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
		if (env->type != LOCAL)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			if (env->type == ENV)
				ft_putstr_print(env->value);
			else
				ft_putstr_print(env->tmp_val);
			ft_putchar(eol);
		}
		env = env->next;
	}


		/*ANTIBUG*/
	if (ANTIBUG == 1)
	{
		t_duo *toto = savior_env(NULL, FALSE);
		ft_putendl("");
		while (toto)
		{printf("[[type (%d) name (%s) value (%s) tmp val (%s)]]\n", toto->type, toto->name, toto->value, toto->tmp_val);
			toto=toto->next;
		}
		printf("\n-----------------------------------\n");
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
	if ((name = srch_begining(arg, '=')) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	if (valid_env_name(name, "env") != FALSE)
	{
		j++;
		value = srch_value(arg, '=');
		change_env(name, value, TMP);
		ft_strdel(&value);
	}
	ft_strdel(&name);
	return (TRUE);
}

int					del_tmp_env(void)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- DEL TMP ENV ------------------", 2);

	t_duo				*env;
	t_duo				*tmp;

	env = savior_env(NULL, FALSE);
	tmp = env;
	while (tmp && tmp->next)
	{
		if (tmp->next->type == TMP)
		{
			free_tduo_link(&(tmp->next));
		}
		else if (tmp->next->type == TMP_ENV || tmp->next->type == TMP_LOCAL)
		{
			ft_strdel(&(tmp->next->tmp_val));
			tmp->next->type -= TMP;
		}
		tmp = tmp->next;
	}
	savior_env(env, TRUE);
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
	j = -5;
	if ((i=ft_strcmp(arg[0], "env")) == 0 || (j = check_builtin(0, cmd, NULL)) != TRUE)
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
	else if (opt[1][1] && arg[*i])
		sh_error(FALSE, 35, NULL, NULL);
	del_tmp_env();
	return (TRUE);
}

int					bi_env(char **arg, char opt[3][2])
{
	t_duo				*save;
	int					opt_i;
	int					len;
	int					i;

	i = (ft_strchr(arg[0], '=') ? 0 : 1);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	len = tbl_len(arg);
	save = cpy_duo(savior_env(NULL, FALSE));
	savior_env(NULL, opt[0][1]);
	if (len > 1)
	{
		if (modif_env(arg, len, &i, opt) == ERROR)
			return (dblstr_duo_ret(ERROR, NULL, NULL, &save));
	}
	else if (i == 1 || (i == 2 && opt[1][1] == 1 && !arg[2]))
	{
		opt_i = (opt[1][1] == 1 ? '\0' : '\n');
		print_env(opt_i);
	}
	if (opt[0][1] == 1)
		savior_env(save, TRUE);
	duo_del(&save);
	return (TRUE);
}
