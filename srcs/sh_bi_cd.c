#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"
#include "libft.h"
#include <stdio.h>

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

int					check_cd_arg(char **arg)
{
	int i;

	i = 1;
	if (arg && arg[i])
	{
		printf("ARG EXIST = YES\n");
		while (arg[i])
		{
			if (arg[i] && arg[i][0] == '-' && arg[i][1])
			{
				printf("last_option : %c\n", check_last_option(arg[i]));
			}
			i++;
		}
	}
	else
		printf("ARG EXIST = NO\n");
	return (TRUE);
}

/*
  static int			cd_option(char *path, char **arg, struct stat stat_buf)
  {
  printf(">>>>>>>>>>>>>>>> CD_OPTION\n");
  (void)path;
  (void)arg;
  int i;

  i = 0;
  if (arg[1] && arg[1][0] == '-' && (check_last_option(arg[1]) == "L") || ft_strcmp(arg[1], "-LP")))
  {
  printf("option = -L\n");
  printf("last option : %c\n", check_last_option(arg[1]));
  if (S_ISLNK(stat_buf.st_mode))
  {
  ft_putstr(">>>>> link\n");
  }
  else
  {
  ft_putstr(">>>>> non_link\n");
  }
  }
  else if (arg[1] && (ft_strcmp(arg[1], "-P") || ft_strcmp(arg[1], "-LP")))
  {
  printf("option = -P\n");
  }
  else
  {
  //error
  }
  return (TRUE);
  }
*/

static int			change_dir(char *path, char **arg)
{
//	printf(">>>>>>>>>>>>>>>> CHANGE_DIR\n");
	struct stat			stat_buf;
	printf(">> print_args dans change_dir\n");
	print_args(arg);
//	check_cd_arg(arg);
	printf("Dans change_dir path = %s\n", path);
	/* if (!stat(path, &stat_buf)) */
	/* 	printf("lstat(path, &stat_buf) SUCCEED"); */
		//	 	cd_option(path, arg, stat_buf); */
	if (chdir(path) == -1)
	{
		if (stat(path, &stat_buf) == 0 && !S_ISDIR(stat_buf.st_mode))
			return (sh_error(FALSE, 16, path, NULL));
		else if ((access(path, F_OK)) == ERROR)
			return (sh_error(FALSE, 17, path, NULL));
		else
			return (sh_error(FALSE, 18, path, NULL));
	}
	else
		printf("chdir(path) SUCCEED\n");
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
//	printf(">>>>>>>>>>>>>>>> HANDLE_CD_ARG\n");
	char				*tmp;

	printf(">> print_args dans handle_cd_arg\n");
	print_args(arg);
	tmp = get_env("OLDPWD", FALSE);
	if (check_opt(arg, i, opt) == ERROR)
	{
		printf(">>>>>>>>>> PROUT\n");
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (!arg[*i])
		*ret = cd_home();
	else if (arg[*i] && arg[*i][0] == '-' && !arg[*i][1])
	{
		printf("tiret seul\n");
		if (tmp)
		{
			*ret = change_dir(tmp, arg);
			printf("*ret = %d\n", *ret);
		}
		else
			return (sh_error(TRUE, 11, NULL, NULL));
	}
	/* else if (arg[*i] && arg[*i][0] && check_last_option(arg[*i]) && arg[2]) */
	/* { */
	/* 	*ret = change_dir(arg[2], arg); */
	/* } */
	else
	{
		printf("DERNIER ELSE HANDLE_CD_ARG\n");
		*ret = change_dir(arg[*i], arg);
		printf("*ret = %d\n", *ret);
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
		printf("handle_cd_arg = FALSE\n");
		return (FALSE);
	}
	if (ret == TRUE)
	{
		printf("OK\n");
		tmp = get_env("PWD", FALSE);
		change_env("OLDPWD", tmp, FALSE);
		path = getcwd(path, MAX_PATH);
		change_env("PWD", path, FALSE);
	}
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (FALSE);
}
