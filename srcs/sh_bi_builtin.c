#include "shell.h"
#include "libft.h"

int					is_builtin(char **cmd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- IS BI --------------------", 2);

	static const char	*bi[] = {"echo", "cd", "setenv", "unsetenv",
								"env", "exit", "export", "unset"};
	int					i;

	i = 0;
	if (cmd)
	{
		while (i < 8)
		{
			if (ft_strcmp(cmd[0], bi[i]) == 0)
				return (i);
			i++;
		}
		if (ft_strchr(cmd[0], '=') && cmd[0][0] != '=')
			return (4);
	}
	return (-1);
}

int					init_opt_tbl(char options[8][3][2])
{
	int					i;
	int					j;

	i = -1;
	while ((++i) < 8)
	{
		j = -1;
		while ((++j) < 3)
		{
			options[i][j][1] = 0;
		}
	}
	return (TRUE);
}

int					handle_builtin(char **cmd, char options[8][3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- HANDLE BI --------------------", 2);
	//attention a modifier aussi les bornes du i qd on rajoute un bi

	int					i;
	int					ret;
	t_duo				*env;
	static const char	*bi[] = {"echo", "cd", "setenv", "unsetenv", "env",
						"exit", "export", "unset"};
	static int			(*tbl_bi[])(char **cmd, t_duo **env, char opt[3][2]) = {&bi_echo,
						&bi_cd, &bi_setenv, &bi_unsetenv, &bi_env, &bi_exit,
						&bi_export, &bi_unset};

	env = savior_env(NULL, FALSE);
	i = 0;
	while (i < 8 && ft_strcmp(cmd[0], bi[i]) != 0)
		i++;
	if (i == 8 && ft_strchr(cmd[0], '='))
		i = 4;
	if ((i < 8 && ft_strcmp(cmd[0], bi[i]) == 0) || ft_strchr(cmd[0], '='))
	{
		if ((ret = tbl_bi[i](cmd, &env, options[i])) == ERROR)
			return (ERROR);
		return (ret);
	}
	if (cmd)
		free_tab(&cmd);
	return (FALSE);
}

int					manage_local_var(char **cmd, int *i)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- MANAGE LOCAL VAR --------------------", 2);

	char				**local_var;
	t_duo				*local_env;

	while (cmd && cmd[*i] && cmd[*i] && ft_strchr(cmd[*i], '='))
		(*i)++;
	if (cmd[*i])
		return (FALSE);
	*i = 0;
	while (cmd && cmd[*i] && cmd[*i] && ft_strchr(cmd[*i], '='))
	{
		local_var = ft_strsplit(cmd[*i], '=');
		if (!valid_env_name(local_var[0], "local") || cmd[*i][0] == '=')
			return (FALSE);
		local_env = savior_local(NULL, FALSE);
		change_env(local_var[0], local_var[1], REV);
		(*i)++;
	}
	return (TRUE);
}

int					check_builtin(int fd, char **cmd, int pipefd_tab[2][2],
					t_lst_fd **lstfd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK BI --------------------", 2);

	static char			options[8][3][2] = {{{'n', 0}, {'e', 0}, {'E', 0}},
	{{'L', 0}, {'P', 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0},
	{0, 0}}, {{'i', 0}, {'0', 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{'p', 0},
	{0, 0}, {0, 0}}, {{'v', 0}, {'f', 0}, {0, 0}}};
	int					ret;
	int					i;

	if (fd == -1)
		return (FALSE);
	i = 0;
	(void)*pipefd_tab;
	init_opt_tbl(options);
	ret = -1;
	if ((ret = manage_local_var(cmd, &i)) == TRUE && cmd[i] == NULL)
		return (TRUE);
	if (is_builtin(cmd) != -1)
	{
		if (handle_builtin(cmd, options) == ERROR)
		{
			close_lstfd(lstfd);
			return (ERROR);
		}
		return (TRUE);
	}
	return (ret);
}
