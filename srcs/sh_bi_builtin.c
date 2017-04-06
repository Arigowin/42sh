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
		if (ft_strchr(cmd[0], '='))
			return (4);
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
	static const char	*options[] = {"neE", "LP", "", "", "iu", "", "p", "vf"};
	static const char	*bi[] = {"echo", "cd", "setenv", "unsetenv", "env",
						"exit", "export", "unset"};
	static int			(*tbl_bi[])(char **cmd, t_duo **env, const char *opt) = {&bi_echo,
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
	char				**cpy;
	t_duo				*local_env;
	int					ret;

	ret = FALSE;
	cpy = cmd;
	while (cpy && cpy[*i] && cpy[*i] && ft_strchr(cpy[*i], '='))
		(*i)++;
	if (cpy[*i])
		return (FALSE);
	*i = 0;
	while (cpy && cpy[*i] && cpy[*i] && ft_strchr(cpy[*i], '='))
	{
		ret = TRUE;
		local_var = ft_strsplit(cpy[*i], '=');
		local_env = savior_local(NULL, FALSE);
		if (local_var && get_env(local_var[0], TRUE))
			change_env(local_var[0], local_var[1], TRUE);
		else if (local_var && get_env(local_var[0], FALSE))
			change_env(local_var[0], local_var[1], FALSE);
		else
			duo_pushback(&local_env, local_var[0], local_var[1]);
		savior_local(local_env, TRUE);
		(*i)++;
	}
	return (ret);
}

int					check_builtin(int fd, char **cmd, int pipefd_tab[2][2],
					t_lst_fd **lstfd)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK BI --------------------", 2);

	int					ret;
	int					i;

	if (fd == -1)
		return (FALSE);
	i = 0;
	(void)*pipefd_tab;
	ret = -1;
	if ((ret = manage_local_var(cmd, &i)) == TRUE && cmd[i] == NULL)
		return (TRUE);
	if (is_builtin(cmd) != -1)
	{
		if (handle_builtin(cmd) == ERROR)
		{
			close_lstfd(lstfd);
			return (ERROR);
		}
		return (TRUE);
	}
	return (ret);
}
