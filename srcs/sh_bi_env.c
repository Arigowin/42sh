#include <unistd.h>
#include "libft.h"
#include "shell.h"

static int			print_env(int eol)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- PRINT ENV ------------------", 2);

	t_duo *env;

	env = savior_env(NULL, FALSE);
	while (env)
	{
		ft_putstr(env->name);
		ft_putchar('=');
		ft_putstr_print(env->value);
		ft_putchar(eol);
		env = env->next;
	}
	return (TRUE);
}

static int			format_env(char *arg)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- FORMAT ENV ------------------", 2);

	int					j;
	char				*name;
	char				*value;

	j = 0;
	while (arg[j] != '=')
		j++;
	name = ft_strsub(arg, 0, j);
	if (valid_env_name(name, "env") != FALSE)
	{
		j++;
		value = ft_strsub(arg, j, ft_strlen(arg) - j);
		change_env(name, value, FALSE);
		ft_strdel(&value);
	}
	ft_strdel(&name);
	return (TRUE);
}

static int			exec_cmd_env(int i, int len, char **arg)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- EXEC CMD ENV ------------------", 2);

	char				**cmd;
	int					pipefd_tab[2][2];
	int					j;

	j = 0;
	cmd = NULL;
	if ((cmd = (char **)malloc(sizeof(char *) * ((len - i) + 1))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	while (arg[i])
	{
		if ((cmd[j] = ft_strdup(arg[i])) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		j++;
		i++;
	}
	cmd[j] = NULL;
	init_pipefd(pipefd_tab);
	if (ft_strcmp(arg[0], "env") && check_builtin(0, cmd, NULL, NULL) != TRUE)
		handle_fork(pipefd_tab, savior_tree(NULL, FALSE), NULL, cmd);
	free_tab(&cmd);
	return (TRUE);
}

int					modif_env(char **arg, int len, int *i, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- MODIF ENV ------------------", 2);

	char				eol;

	eol = (opt[1][1] == 1 ? '\0' : '\n');
	while (arg[*i])
	{
		if (ft_strchr(arg[*i], '=') != NULL)
			format_env(arg[*i]);
		else
			break ;
		(*i)++;
	}
	if (*i < len && opt[1][1] == 0)
		exec_cmd_env(*i, len, arg);
	else if (opt[1][1] == 0 || (opt[1][1] == 1 && !arg[*i]))
		print_env(eol);
	return (TRUE);
}

int					bi_env(char **arg, t_duo **env, char opt[3][2])
{
	t_duo				*env_tmp;
	int					opt_i;
	int					len;
	int					i;

	i = (ft_strchr(arg[0], '=') ? 0 : 1);
	env_tmp = cpy_duo(*env);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	len = (tbl_len(arg));
	savior_env(NULL, opt[0][1]);
	if (len > 1)
	{
		if (modif_env(arg, len, &i, opt) == ERROR)
			return (ERROR);
	}
	if (i == 1 || (i == 2 && opt[1][1] == 1 && !arg[2]))
	{
		opt_i = (opt[1][1] == 1 ? '\0' : '\n');
		print_env(opt_i);
	}
	else if (opt[1][1] && arg[i])
		sh_error(FALSE, 35, NULL, NULL);
	savior_env(env_tmp, TRUE);
	return (TRUE);
}
