#include <unistd.h>
#include "libft.h"
#include "shell.h"

int					print_env(int eol)
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

int					format_env(char *arg)
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

int					del_tmp_env(int opt_i)
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
	if (opt_i)
		duo_del(&env);
	savior_env(env, TRUE);
	return (TRUE);
}

int					init_env_i(t_duo **env)
{
	*env = savior_env(NULL, FALSE);
	duo_del(env);
	*env = savior_env(NULL, TRUE);
	return (TRUE);
}

int					bi_env(char **arg, char opt[3][2])
{
	t_duo				*save;
	t_duo				*env;
	int					len;
	int					i;

	i = (ft_strchr(arg[0], '=') ? 0 : 1);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	len = tbl_len(arg);
	save = cpy_duo(savior_env(NULL, FALSE));
	if (opt[0][1])
		init_env_i(&env);
	if (len > 1)
	{
		if (modif_env(arg, len, &i, opt) == ERROR)
			return (dblstr_duo_ret(ERROR, NULL, NULL, &save));
	}
	else if (i == 1 || (i == 2 && opt[1][1] == 1 && !arg[2]))
		print_env((opt[1][1] == 1 ? '\0' : '\n'));
	if (opt[0][1] == 1)
		savior_env(save, TRUE);
	else
		duo_del(&save);
	return (TRUE);
}
