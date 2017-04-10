#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "shell.h"
#include "libft.h"

static int			manage_cd_errors(char *pth, struct stat stat_bf, int stat_r)
{
	if (!stat_r && !S_ISDIR(stat_bf.st_mode))
		return (sh_error(FALSE, 16, pth, NULL));
	else if ((access(pth, F_OK)) == ERROR)
		return (sh_error(FALSE, 17, pth, NULL));
	else
		return (sh_error(FALSE, 18, pth, NULL));
}

int					absolute_link_path_builder(char **path, char *env_pwd)
{
	char				*new_path;
	char				*tmp_path;

	new_path = NULL;
	tmp_path = ft_strjoin(env_pwd, "/");
	ft_strdel(&env_pwd);
	if ((env_pwd = ft_strdup(tmp_path)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	ft_strdel(&tmp_path);
	new_path = ft_strjoin(env_pwd, *path);
	ft_strdel(&env_pwd);
	ft_strdel(path);
	if ((*path = ft_strdup(new_path)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	ft_strdel(&new_path);
	return (TRUE);
}

static int			getcwd_link_path(char **path, char last_opt)
{
	char				*env_pwd;
	int					i;
	int					len;

	if ((env_pwd = get_env("PWD", FALSE)) == NULL)
		env_pwd = getcwd(NULL, 0);
	i = ft_strlen(env_pwd) - 1;
	len = 0;
	if (!ft_strcmp(*path, "..") && (!last_opt || last_opt == 'L') && i)
	{
		ft_strdel(path);
		while (env_pwd[i--] != '/')
			len++;
		*path = ft_strsub(env_pwd, 0, (ft_strlen(env_pwd) - len - 1));
	}
	else if (env_pwd[i] != '/')
		absolute_link_path_builder(path, env_pwd);
	return (TRUE);
}

static int			switch_env_pwd(char *path, int is_symlink)
{
	char				*old_pwd;
	char				*new_path;

	old_pwd = get_env("PWD", FALSE);
	if (!is_symlink)
		new_path = getcwd(NULL, 0);
	else
		new_path = path;
	change_env("OLDPWD", old_pwd, FALSE);
	change_env("PWD", new_path, FALSE);
	ft_strdel(&new_path);
	ft_strdel(&old_pwd);
	return (0);
}

static int			logical_change_dir(char **path, char last_opt, int *ret)
{
	struct stat			stat_buf;
	int					stat_ret;

	if (**path != '/')
		getcwd_link_path(path, last_opt);
	stat_ret = lstat(*path, &stat_buf);
	if (chdir(*path) == ERROR)
		manage_cd_errors(*path, stat_buf, stat_ret);
	if (!stat_ret && S_ISLNK(stat_buf.st_mode))
		switch_env_pwd(*path, TRUE);
	else if (!stat_ret && !S_ISLNK(stat_buf.st_mode))
		switch_env_pwd(*path, FALSE);
	return (*ret = TRUE);
}

static int			physical_change_dir(char **path, int *ret)
{
	struct stat			stat_buf;
	int					stat_ret;

	stat_ret = stat(*path, &stat_buf);
	if (!stat_ret && chdir(*path) == -1)
		manage_cd_errors(*path, stat_buf, stat_ret);
	ft_strdel(path);
	if ((*path = ft_strdup(getcwd(NULL, 0))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	switch_env_pwd(*path, TRUE);
	return (*ret = TRUE);
}

static int			exec_change_dir(char *path, char lopt, int *ret)
{
	if (lopt == 'L' || !lopt)
		logical_change_dir(&path, lopt, ret);
	else if (lopt == 'P')
		physical_change_dir(&path, ret);
	return (TRUE);
}

static int			cd_home(char last_opt)
{
	char				*path;
	int					ret;

	ret = TRUE;
	if ((path = get_env("HOME", FALSE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	exec_change_dir(path, last_opt, &ret);
	return (ret);
}

static int			handle_cd_arg(int *ret, char **arg, char *last_opt, int i)
{
	char				*path;
	char				*old_pwd;

	path = NULL;
	old_pwd = get_env("OLDPWD", FALSE);
	if (i == 1 || (i > 1 && *last_opt && arg[i - 1] && arg[i - 1][0] == '-'
				   && ft_strcmp(arg[i - 1], "-")))
		*ret = cd_home(*last_opt);
	else if (i > 1 && ft_strcmp(arg[i - 1], "-"))
	{
		if ((path = ft_strdup(arg[i - 1])) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		exec_change_dir(path, *last_opt, ret);
	}
	else if (i > 1 && !ft_strcmp(arg[i - 1], "-"))
	{
		if ((path = ft_strdup(old_pwd)) == NULL)
			return (sh_error(TRUE, 11, NULL, NULL));
		ft_putendl(path);
		exec_change_dir(path, *last_opt, ret);
	}
	return (TRUE);
}

int					bi_cd(char **arg, t_duo **env, const char *opt)
{
	int					i;
	int					ret;
	char				last_opt;

	(void)env;
	i = 0;
	ret = TRUE;
	if (check_opt(arg, &i, opt, &last_opt) == ERROR)
		return (FALSE);
	handle_cd_arg(&ret, arg, &last_opt, i);
	return (FALSE);
}
