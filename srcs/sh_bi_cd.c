#include <sys/stat.h>
#include "shell.h"
#include "libft.h"

static int			physical_change_dir(char **path)
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
	return (TRUE);
}

static int			exec_change_dir(char **path, char lopt)
{
	if (lopt == 'L' || !lopt)
		logical_change_dir(path, lopt);
	else if (lopt == 'P')
		physical_change_dir(path);
	return (TRUE);
}

static int			cd_home(char last_opt)
{
	char				*path;

	if ((path = get_env("HOME", ENV, TRUE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	exec_change_dir(&path, last_opt);
	ft_strdel(&path);
	return (TRUE);
}

static int			handle_cd_arg(char **arg, char *last_opt, int i)
{
	char				*path;
	char				*old_pwd;

	path = NULL;
	printf("xxxarg [%s], i [%d]\n", arg[i - 1], i);
	if (arg[i] == NULL)
		cd_home(*last_opt);
	else if (ft_strcmp(arg[i], "-") == 0)
	{
		old_pwd = get_env("OLDPWD", ENV, TRUE);
		if ((path = ft_strdup(old_pwd)) == NULL)
			return (sh_error(TRUE, 11, NULL, NULL));
		ft_putendl(path);
		exec_change_dir(&path, *last_opt);
		ft_strdel(&old_pwd);
		ft_strdel(&path);
	}
	else
	{
		if ((path = ft_strdup(arg[i])) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		exec_change_dir(&path, *last_opt);
		ft_strdel(&path);
	}
	return (TRUE);
}

int					bi_cd(char **arg, char opt[3][2])
{
	int					i;
	char				last_opt;

	i = 1;
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	last_opt = (opt[1][1] == 1 ? 'P' : 'L');
	printf("arg [%s], i [%d]\n", arg[i], i);
	handle_cd_arg(arg, &last_opt, i);
	return (TRUE);
}
