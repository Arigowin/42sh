#include <unistd.h>
#include "libft.h"
#include "shell.h"


int					env_i(char **arg, char curr_opt, char *bi)
{
	(void)arg;
	(void)curr_opt;
	(void)bi;
	savior_env(NULL, TRUE);
	return (TRUE);
}

int					print_env(t_duo *env)
{
	while (env)
	{
		ft_putstr(env->name);
		ft_putchar('=');
		ft_putstr_print(env->value);
		ft_putchar('\n');
		env = env->next;
	}
	return (TRUE);
}

int					format_env(char *arg, int *nb)
{
	int					j;
	char				*key;
	char				*value;

	j = 0;
	while (arg[j] != '=')
		j++;
	key = ft_strsub(arg, 0, j);
	if (valid_env_name(key, "env") != FALSE)
	{
		j++;
		value = ft_strsub(arg, j, ft_strlen(arg) - j);
		change_env(key, value, BOTH);
		ft_strdel(&value);
		(*nb)++;
	}
	ft_strdel(&key);
	return (TRUE);
}

int					exec_cmd_env(int i, int len, char **arg)
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
	handle_fork(pipefd_tab, savior_tree(NULL, FALSE), NULL, cmd);
	free_tab(&cmd);
	return (TRUE);
}

int					bi_env(char **arg, t_duo **env, char opt[3][2])
{
	t_duo				*env_tmp;
	int					len;
	int					i;

	len = tbl_len(arg);
	i = (ft_strchr(arg[0], '=') ? 0 : 1);
	env_tmp = cpy_duo(*env);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	if (len > 1)
	{
		if (modif_env(arg, savior_env(NULL, FALSE), len, i) == ERROR)
			return (ERROR);
	}
	else if (i == 1)
		print_env(env_tmp);
	savior_env(env_tmp, TRUE);
	return (TRUE);
}
