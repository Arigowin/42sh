#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"
#include "libft.h"
#include <stdio.h>

char				check_last_option(char *str)
{
	char car;

	car = *(str + (ft_strlen(str) - 1));
	return (car);
}

int					check_cd_arg(char **arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] && arg[i][0] == '-' && arg[i][1])
		{
			printf("last_option : %d\n", check_last_option(arg[1]));
		}
	}
	return (TRUE);
}

static int			cd_option(char *path, char **arg, struct stat stat_buf)
{
	printf(">>>>>>>>>>>>>>>> CD_OPTION\n");
	(void)path;
	(void)arg;
	int i;

	i = 0;
	if (arg[1] && ft_strcmp(arg[1], "-L"))
	{
		printf("prout\n");
		printf("last option : %c\n", check_last_option(arg[1]));
		if (S_ISLNK(stat_buf.st_mode))
		{
			ft_putstr(">>>>> link\n");
		}
		else
		{
			;
		}
	}
	else if (ft_strcmp(arg[1], "-P") || ft_strcmp(arg[1], "-LP"))
	{
		;
	}
	else
	{
		//error
	}
	return (TRUE);
}

static int			change_dir(char *path, char **arg)
{
	printf(">>>>>>>>>>>>>>>> CHANGE_DIR\n");
	struct stat			stat_buf;

	(void)arg;
	if (!lstat(path, &stat_buf))
		cd_option(path, arg, stat_buf);
	if (chdir(path) == -1)
	{
		printf("XXXX OUPS\n");
		if (stat(path, &stat_buf) == 0 && !S_ISDIR(stat_buf.st_mode))
			return (sh_error(FALSE, 16, path, NULL));
		else if ((access(path, F_OK)) == ERROR)
			return (sh_error(FALSE, 17, path, NULL));
		else
			return (sh_error(FALSE, 18, path, NULL));
	}
	return (TRUE);
}

static int			cd_home(void)
{
	char				*path;
	int					ret;

	if ((path = get_env("HOME", FALSE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	ret = change_dir(path, NULL);
	ft_strdel(&path);
	return (ret);
}

static int			handle_cd_arg(int *i, int *ret, char **arg, const char *opt)
{
	printf(">>>>>>>>>>>>>>>> HANDLE_CD_ARG\n");
	char				*tmp;

//	print_arg(arg);
	tmp = get_env("OLDPWD");
	/* if (check_opt(arg, i) == ERROR) */
	/* { */
	/* 	ft_strdel(&tmp); */
	/* 	return (FALSE); */
	/* } */
	if (!arg[*i])
		*ret = cd_home();
	else if (arg[*i] && arg[*i][0] == '-' && !arg[*i][*i])
	{
		if (tmp)
			*ret = change_dir(tmp, arg);
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	else if (arg[*i] && arg[*i][0] && check_last_option(arg[*i]) && arg[2])
	{
		*ret = change_dir(arg[2], arg);
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
		return (FALSE);
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
