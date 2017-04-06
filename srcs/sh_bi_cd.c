#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "shell.h"
#include "libft.h"

void				print_args(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		printf(">>> %s\n", arg[i]);
		i++;
	}
}

char				check_last_option(char *str)
{
	char car;

	car = *(str + (ft_strlen(str) - 1));
	return (car);
}

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

/*
** stat_ret = lstat(path, &stat_buf);
*/
static int			change_dir(char *path, char last_opt, char **arg)
{
	struct stat			stat_buf;
	int					stat_ret;

	(void)arg;
	stat_ret = fstatat(AT_FDCWD, path, &stat_buf, AT_SYMLINK_NOFOLLOW);
	if (!stat_ret)
		cd_option(path, last_opt, stat_buf);
	if (chdir(path) == -1)
	{
		if (!stat_ret && !S_ISDIR(stat_buf.st_mode))
			return (sh_error(FALSE, 16, path, NULL));
		else if ((access(path, F_OK)) == ERROR)
			return (sh_error(FALSE, 17, path, NULL));
		else
			return (sh_error(FALSE, 18, path, NULL));
	}
	else
		printf("chdir(path) -----> SUCCEED\n");
	return (TRUE);
}

static int			cd_home(void)
{
	char				*path;
	int					ret;

	if ((path = get_env("HOME", FALSE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	ret = change_dir(path, 0, NULL);
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
	printf("+++++++++++ handle_cd_arg > last_opt : %c\n", last_opt);
	if (!arg[*i])
		*ret = cd_home();
	else if (arg[*i] && arg[*i][0] == '-' && !arg[*i][1])
	{
		if (tmp)
			*ret = change_dir(tmp, last_opt, arg);
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	else
	{
		*ret = change_dir(arg[*i], last_opt, arg);
	}
	ft_strdel(&tmp);
	return (TRUE);
}

int					bi_cd(char **arg, t_duo **env, const char *opt)
{
	char				*tmp;
	char				*path;
	int					i;
	int					ret;

	(void)env;
	i = 1;
	ret = 0;
	tmp = NULL;
	path = NULL;
	if (handle_cd_arg(&i, &ret, arg, opt) == FALSE)
	{
		return (FALSE);
	}
	if (ret == TRUE)
	{
		tmp = get_env("PWD", FALSE);
		change_env("OLDPWD", tmp, FALSE);
		path = getcwd(path, MAX_PATH);
		change_env("PWD", path, FALSE);
	}
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (FALSE);
}
