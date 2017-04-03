#include "shell.h"
#include "libft.h"

int					is_builtin(char **cmd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- IS BI --------------------", 2);

	static const char	*bi[] = {"echo", "cd", "setenv", "unsetenv",
								"env", "exit", "export"};
	int					i;

	i = 0;
	if (cmd)
	{
		while (i < 7)
		{
			if (ft_strcmp(cmd[0], bi[i]) == 0)
				return (i);
			i++;
		}
	}
	return (-1);
}

int					handle_builtin(char **cmd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- HANDLE BI --------------------", 2);
	//attention a modifier aussi les bornes du i qd on rajoute un bi

	int					i;
	int					ret;
	t_duo				*env;
	static const char	*bi[] = {"echo", "cd", "setenv", "unsetenv", "env",
						"exit", "export"};
	static int			(*tbl_bi[])(char **cmd, t_duo **env) = {&bi_echo,
						&bi_cd, &bi_setenv, &bi_unsetenv, &bi_env, &bi_exit,
						&bi_export};

	env = savior_env(NULL, FALSE);
	i = 0;
	while (i < 7 && ft_strcmp(cmd[0], bi[i]) != 0)
		i++;
	if (i < 7 && ft_strcmp(cmd[0], bi[i]) == 0)
	{
		if ((ret = tbl_bi[i](cmd, &env)) == ERROR)
			return (ERROR);
		return (ret);
	}
	printf("TROLOLO POUET TOTO\n");
	if (cmd)
		free_tab(&cmd);
	return (FALSE);
}

int					manage_local_var(char *str)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- MANAGE LOCAL VAR --------------------", 2);

	char				**local_var;
	t_duo				*local_env;

	local_var = ft_strsplit(str, '=');
	local_env = savior_local(NULL, FALSE);
	if (get_env(local_var[0], TRUE))
		change_env(local_var[0], local_var[1], TRUE);
	else
		duo_pushback(&local_env, local_var[0], local_var[1]);
	savior_local(local_env, TRUE);
	return (TRUE);
}

int					check_builtin(int fd, char **cmd, int pipefd_tab[2][2],
					t_lst_fd **lstfd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK BI --------------------", 2);

	int					ret;

	if (fd == -1)
		return (FALSE);
	(void)*pipefd_tab;
	ret = -1;
	if (ft_strchr(cmd[0], '=') && manage_local_var(cmd[0]) == TRUE)
		return (TRUE);
	if (is_builtin(cmd) != -1)
	{
		if ((ret = handle_builtin(cmd)) == ERROR)
		{
			close_lstfd(lstfd);
			return (ERROR);
		}
		return (TRUE);
	}
	return (FALSE);
}
