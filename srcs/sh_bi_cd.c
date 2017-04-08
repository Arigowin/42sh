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

static int			getcwd_link_path(char **path)
{
	printf("[ getcwd_link_path ]\n");
	char				*tmp_path;
	char				*new_path;
	
	tmp_path = NULL;
	new_path = NULL;
	if (**(path) != '/' || **(path) != '~')
	{
		if (!access(*path, F_OK))
		{
			tmp_path = ft_strjoin(get_env("PWD", FALSE), "/");
			new_path = ft_strjoin(tmp_path, *path);
			ft_strdel(&tmp_path);
			ft_strdel(path);
			*path = ft_strdup(new_path);
			ft_strdel(&new_path);
			return (TRUE);
		}
		else
			return (ERROR);
	}
	return (FALSE);
}

static int			switch_env_pwd(char *path)
{
	printf("[ switch_env_pwd ]\n");
	char				*old_pwd;

	old_pwd = get_env("PWD", FALSE);
	printf(">> future old_pwd (actuel pwd dans env) = %s\n", old_pwd);
	printf("---> path = %s\n", path);
	change_env("OLDPWD", old_pwd, FALSE);
	change_env("PWD", path, FALSE);
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

	stat_ret = lstat(*path, &stat_buf);
	if (!stat_ret && S_ISLNK(stat_buf.st_mode))
	{
		printf("link | last_opt = %c, path : %s\n", last_opt, *path);
		getcwd_link_path(path);
		switch_env_pwd(*path);
		if (chdir(*path) == -1)
			manage_cd_errors(*path, stat_buf, stat_ret);
		/* else */
		/* 	switch_env_pwd(*path); */
	}
	else
	{
		printf("non_link | last_opt = %c, path : %s\n", last_opt, *path);
		if (chdir(*path) == -1)
			manage_cd_errors(*path, stat_buf, stat_ret);
		switch_env_pwd(*path);
		/* else */
		/* { */
		/* 	switch_env_pwd(*path); */
		/* } */
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
	switch_env_pwd(*path);
	if (!stat_ret && chdir(*path) == -1)
		manage_cd_errors(*path, stat_buf, stat_ret);
	/* else */
	/* 	switch_env_pwd(*path); */
	*ret = TRUE;
	return (TRUE);
}

static int			exec_change_dir(char *path, char lopt, int *ret)
{
	if (lopt == 'L' || !lopt)
		logical_change_dir(&path, lopt, ret);
	else if (lopt == 'P')
		physical_change_dir(&path, lopt, ret);
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

	printf("[ handle cd arg ]\n");
	path = NULL;
	if (check_opt(arg, &i, opt, &last_opt) == ERROR)
		return (FALSE);
	if (!arg[1] || (arg[1] && last_opt))
		*ret = cd_home(last_opt);
	else if (arg[1] && !ft_strcmp(arg[1], "-") && old_pwd)
	{
		printf("++++++++++++++ old_pwd si tiret : %s\n", old_pwd);
		path = ft_strdup(old_pwd);
		if (old_pwd)
		{
			exec_change_dir(path, last_opt, ret);
			ft_strdel(&path);
		}
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	else if (arg[1] && !arg[2])
	{
		path = ft_strdup(arg[1]);
		exec_change_dir(path, last_opt, ret);
	}
	else if (arg[1] && arg[1][0] == '-' && last_opt && arg[2])
	{
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
