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

/*
static int			cd_option(char *path, char last_opt, struct stat stat_buf)
{
	(void)last_opt;
	(void)path;
	if (S_ISLNK(stat_buf.st_mode))
	{
		ft_putstr(">>>>> link\n");
	}
	else
	{
		ft_putstr(">>>>> non_link\n");
	}
	return (TRUE);
}
*/

static int			manage_cd_errors(char *path, struct stat stat_buf, int stat_ret)
{
	if (!stat_ret && !S_ISDIR(stat_buf.st_mode))
		return (sh_error(FALSE, 16, path, NULL));
	else if ((access(path, F_OK)) == ERROR)
		return (sh_error(FALSE, 17, path, NULL));
	else
		return (sh_error(FALSE, 18, path, NULL));
}

/*
** stat_ret = lstat(path, &stat_buf);
** cd_option(path, last_opt, stat_buf);
*/

static int			change_dir(char **path, char last_opt, char **arg, int *ret)
{
	struct stat			stat_buf;
	int					stat_ret;
	char				*tmp_path;
	char				*new_path;

	(void)arg;
	(void)last_opt;
	tmp_path = ft_strjoin(get_env("PWD", FALSE), "/");
	new_path = NULL;
	stat_ret = lstat(*path, &stat_buf);
	if (!stat_ret)
	{
		if (S_ISLNK(stat_buf.st_mode))
		{
			*ret = TRUE;
			new_path = ft_strjoin(tmp_path, *path);
			ft_strdel(&tmp_path);
			ft_strdel(path);
			*path = ft_strdup(new_path);
			printf("new_path : %s\n", *path);
			if (chdir(*path) == -1)
				manage_cd_errors(new_path, stat_buf, stat_ret);
			else
				change_env("PWD", *path, FALSE);
			printf(">>> link\n");
			ft_strdel(path);
		}
		else
		{
			*ret = FALSE;
			if (chdir(*path) == -1)
				manage_cd_errors(*path, stat_buf, stat_ret);
			printf(">>> non_link\n");
		}
	}
	ft_strdel(&new_path);
	return (TRUE);
}

static int			switch_env_pwd()
{
	char				*tmp;
	char				*path;

	tmp = get_env("PWD", FALSE);
	path = NULL;
	change_env("OLDPWD", tmp, FALSE);
	path = getcwd(path, MAX_PATH);
	change_env("PWD", path, FALSE);
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (0);
}

static int			cd_home(void)
{
	char				*path;
	int					ret;
	int					ret2;

	if ((path = get_env("HOME", FALSE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	ret = change_dir(&path, 0, NULL, &ret2);
	switch_env_pwd();
	ft_strdel(&path);
	return (ret);
}

static int			handle_cd_arg(int *i, int *ret, char **arg, const char *opt)
{
	char				*tmp;
	char				last_opt;

	tmp = get_env("OLDPWD", FALSE);
	if (check_opt(arg, i, opt, &last_opt) == ERROR)
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	/*
	if (!arg[*i])
		*ret = cd_home();
	*/
	else if (arg[*i] && arg[*i][0] == '-' && !arg[*i][1])
	{
		if (tmp)
		{
			change_dir(&tmp, last_opt, arg, ret);
			ft_putendl(tmp);
		}
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	else
		change_dir(&arg[*i], last_opt, arg, ret);
	ft_strdel(&tmp);
	return (TRUE);
}

int					bi_cd(char **arg, t_duo **env, const char *opt)
{
	int					i;
	int					ret;
	char				last_opt;

	(void)env;
	i = 1;
	ret = TRUE;
	last_opt = '\0';
	check_opt(arg, &i, opt, &last_opt);
	printf("last_option : %c\n", last_opt);
	if (last_opt)
		printf("last_opt = %c\n", last_opt);
	if (!arg[1])
		cd_home();
	else if (!last_opt || last_opt == 'L')
	{
		switch_env_pwd();
		if (handle_cd_arg(&i, &ret, arg, opt) == FALSE)
			return (FALSE);
	}
	else if (last_opt == 'P')
	{
		if (handle_cd_arg(&i, &ret, arg, opt) == FALSE)
			return (FALSE);
		switch_env_pwd();
	}
	return (FALSE);
}
