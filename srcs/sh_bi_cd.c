#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "shell.h"
#include "libft.h"

char				check_last_option(char *str)
{
	char car;

	car = *(str + (ft_strlen(str) - 1));
	return (car);
}

static int			manage_cd_errors(char *path, struct stat stat_buf, int stat_ret)
{
	if (!stat_ret && !S_ISDIR(stat_buf.st_mode))
		return (sh_error(FALSE, 16, path, NULL));
	else if ((access(path, F_OK)) == ERROR)
		return (sh_error(FALSE, 17, path, NULL));
	else
		return (sh_error(FALSE, 18, path, NULL));
}

static int			getcwd_link_path(char **path, int is_symlink, char last_opt)
{
	printf("[ getcwd_link_path ]\n");
	char				*tmp_path;
	char				*new_path;
	char				*env_pwd;
	int					i;
	int					len;
	
	(void)is_symlink;
	tmp_path = NULL;
	new_path = NULL;
	env_pwd = get_env("PWD", FALSE);
	i = ft_strlen(env_pwd) -1;
	printf("i = %d\n", i);
	len = 0;
	printf(">>>>>>>> path transmis = %s\n", *path);
	if (!ft_strcmp(*path, "..") && (!last_opt || last_opt == 'L'))
	{
		ft_strdel(path);
		while (env_pwd[i] != '/')
		{
			i--;
			len++;
		}
//		printf("i = %d | len = %d\n", i, len);
//		printf(">>>> sous chaine a supprimer %s\n", (env_pwd + i));
//		printf(">>>> sous chaine a conserver %s\n",
//			   ft_strsub(env_pwd, 0, (ft_strlen(env_pwd) - len - 1)));
		*path = ft_strsub(env_pwd, 0, (ft_strlen(env_pwd) - len - 1));
	}
	else if (env_pwd[ft_strlen(env_pwd) - 1] != '/')
	{
		tmp_path = ft_strjoin(env_pwd, "/");
		ft_strdel(&env_pwd);
		env_pwd = ft_strdup(tmp_path);
		ft_strdel(&tmp_path);
		new_path = ft_strjoin(env_pwd, *path);
		ft_strdel(&env_pwd);
		ft_strdel(path);
		*path = ft_strdup(new_path);
		ft_strdel(&new_path);
	}
	printf(">>>>>>>>>>>>>>>>> new path = %s\n", *path);
	if (!access(*path, F_OK))
		return (TRUE);
	return (ERROR);
}

static int			switch_env_pwd(char *path, int is_symlink)
{
	printf("[ switch_env_pwd ], path = %s, is_symlink = %d\n", path, is_symlink);
	char				*old_pwd;
	char				*new_path;

	(void)path;
	old_pwd = get_env("PWD", FALSE);
	new_path = NULL;
	if (!is_symlink)
	{
		new_path = getcwd(NULL, 0);
		printf("new_path = %s\n", new_path);
	}
	else
		new_path = path;
	printf(">> future old_pwd (actuel pwd dans env) = %s\n", old_pwd);
	printf("---> new_path = %s\n", new_path);
	change_env("OLDPWD", old_pwd, FALSE);
	change_env("PWD", new_path, FALSE);
	ft_strdel(&new_path);
	ft_strdel(&old_pwd);
	return (0);
}


/*
** stat_ret = lstat(path, &stat_buf);
** cd_option(path, last_opt, stat_buf);
*/

static int			logical_change_dir(char **path, char last_opt, int *ret)
{
	printf("[ logical_change_dir ] : ");
	struct stat			stat_buf;
	int					stat_ret;
	char				*cwd;

	stat_ret = lstat(*path, &stat_buf);
	cwd = NULL;
	if (!stat_ret && S_ISLNK(stat_buf.st_mode))
	{
		printf("link | last_opt = %c, path : %s\n", last_opt, *path);
		getcwd_link_path(path, TRUE, last_opt);
		printf("path apres getcwd_link_path et avant chdir(path) : %s\n", *path);
		if (chdir(*path) == -1)
			manage_cd_errors(*path, stat_buf, stat_ret);
		switch_env_pwd(*path, TRUE);
	}
	else if (!stat_ret && !S_ISLNK(stat_buf.st_mode))
	{
		printf("non_link | last_opt = %c, path : %s\n", last_opt, *path);
		if (**path != '/')
		{
			getcwd_link_path(path, FALSE, last_opt);
			printf("path apres getcwd_link_path = %s\n", *path);
		}
		if (chdir(*path) == -1)
			manage_cd_errors(*path, stat_buf, stat_ret);
		switch_env_pwd(*path, FALSE);
		printf("fin logical change dir\n");
	}
	*ret = TRUE;
	return (TRUE);
}

static int			physical_change_dir(char **path, char last_opt, int *ret)
{
	struct stat			stat_buf;
	int					stat_ret;

	printf("[ physical change dir ] last_opt = %c, path : %s\n", last_opt, *path);
	stat_ret = stat(*path, &stat_buf);
	switch_env_pwd(*path, TRUE);
	if (!stat_ret && chdir(*path) == -1)
		manage_cd_errors(*path, stat_buf, stat_ret);
	*ret = TRUE;
	return (TRUE);
}

static int			exec_change_dir(char *path, char lopt, int *ret)
{
	printf("[ exec_change_dir ]\n");
	if (lopt == 'L' || !lopt)
		logical_change_dir(&path, lopt, ret);
	else if (lopt == 'P')
		physical_change_dir(&path, lopt, ret);
//	ft_strdel(&path);
	return (TRUE);
}

static int			cd_home(char last_opt)
{
	char				*path;
	int					ret;

	ret = TRUE;
	printf("[ cd home ]\n");
	if ((path = get_env("HOME", FALSE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	if (last_opt == 'L' || !last_opt)
		logical_change_dir(&path, last_opt, &ret);
	else if (last_opt == 'P')
		physical_change_dir(&path, last_opt, &ret);
	return (ret);
}

static int			handle_cd_arg(int *ret, char **arg, const char *opt, char *old_pwd)
{
	int					i;
	char				last_opt;
	char				*path;

	path = NULL;
	if (check_opt(arg, &i, opt, &last_opt) == ERROR)
		return (FALSE);
	printf("[ handle_cd arg ] last_opt : %c\n", last_opt);
	if (!arg[1] || (arg[1] && last_opt && !arg[2]))
		*ret = cd_home(last_opt);
	else if (arg[1] && !ft_strcmp(arg[1], "-"))
	{
		printf("++++++++++++++ case1 old_pwd si tiret : %s\n", old_pwd);
		path = ft_strdup(old_pwd);
		if (old_pwd)
			exec_change_dir(path, last_opt, ret);
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	else if (arg[1] && arg[1][0] != '-' && !last_opt && !arg[2])
	{
		printf("++++++++++++++ case2 arg[1] = %s, arg[2] = %s\n", arg[1], arg[2]);
		path = ft_strdup(arg[1]);
		exec_change_dir(path, last_opt, ret);
	}
	else if (arg[1] && arg[1][0] == '-' && last_opt && arg[2])
	{
		printf("++++++++++++++ case3 arg[1] = %s, arg[2] = %s\n", arg[1], arg[2]);
		path = ft_strdup(arg[2]);
		exec_change_dir(path, last_opt, ret);
	}
	return (TRUE);
}

int					bi_cd(char **arg, t_duo **env, const char *opt)
{
	int					i;
	int					ret;
	char				last_opt;
	char				*old_pwd;

	(void)env;
	i = 0;
	ret = TRUE;
	last_opt = '\0';
	old_pwd = get_env("OLDPWD", FALSE);
	if (check_opt(arg, &i, opt, &last_opt) == ERROR)
		return (FALSE);
	handle_cd_arg(&ret, arg, opt, old_pwd);
	ft_strdel(&old_pwd);
	return (FALSE);
}
