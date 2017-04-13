#include <sys/stat.h>
#include "shell.h"
#include "libft.h"

static int			physical_change_dir(char **path, int *ret)
{
	struct stat			stat_buf;
	int					stat_ret;

	stat_ret = stat(*path, &stat_buf);
	if (stat_ret == ERROR || chdir(*path) == -1)
		manage_cd_errors(*path, stat_buf, stat_ret);
	ft_strdel(path);
	if ((*path = getcwd(NULL, 0)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	switch_env_pwd(*path, TRUE);
	return (*ret = TRUE);
}

static int			exec_change_dir(char **path, char lopt, int *ret)
{
	if (lopt == 'L' || !lopt)
		logical_change_dir(path, lopt, ret);
	else if (lopt == 'P')
		physical_change_dir(path, ret);
	return (TRUE);
}

static int			cd_home(char last_opt)
{
	char				*path;
	int					ret;

	ret = TRUE;
	if ((path = get_env("HOME", ENV, TRUE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	exec_change_dir(&path, last_opt, &ret);
	ft_strdel(&path);
	return (ret);
}

static int			handle_cd_arg(int *ret, char **arg, char *last_opt, int i)
{
	char				*path;
	char				*old_pwd;

	path = NULL;
	if (i == 1 || (i > 1 && *last_opt && arg[i - 1] && arg[i - 1][0] == '-'
	&& ft_strcmp(arg[i - 1], "-")))
		*ret = cd_home(*last_opt);
	else if (i > 1 && ft_strcmp(arg[i - 1], "-"))
	{
		if ((path = ft_strdup(arg[i - 1])) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		exec_change_dir(&path, *last_opt, ret);
		ft_strdel(&path);
	}
	else if (i > 1 && !ft_strcmp(arg[i - 1], "-"))
	{
		old_pwd = get_env("OLDPWD", ENV, TRUE);
		if ((path = ft_strdup(old_pwd)) == NULL)
			return (sh_error(TRUE, 11, NULL, NULL));
		ft_putendl(path);
		exec_change_dir(&path, *last_opt, ret);
		ft_strdel(&old_pwd);
		ft_strdel(&path);
	}
	return (TRUE);
}

int					bi_cd(char **arg, char opt[3][2])
{
	int					i;
	int					ret;
	char				last_opt;

	i = 1;
	ret = TRUE;
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	while (arg[i] && arg[i][0] == '-' && arg[i][1])
		i++;
	i += (arg[i] ? 1 : 0);
	last_opt = (opt[1][1] == 1 ? 'P' : 'L');
	handle_cd_arg(&ret, arg, &last_opt, i);
	return (FALSE);
}
