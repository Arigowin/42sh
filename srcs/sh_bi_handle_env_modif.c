#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value, t_env type)
{
	t_duo 				*env;

	env = savior_env(NULL, FALSE);
	if (name == NULL)
		return (sh_error(TRUE, 26, "setenv", NULL));
	if (value && value[0] == 26)
		duo_pushback(&env, name, "", type);
	else
		duo_pushback(&env, name, value, type);
	savior_env(env, TRUE);
	return (TRUE);
}

int					change_env(char *name, char *val, t_env type)
{
	t_duo				*tmp;
	int					ret;

	ret = FALSE;
	tmp = savior_env(NULL, FALSE);
	while (tmp)
	{
		if (tmp && name && ft_strcmp(tmp->name, name) == 0)
		{
			if (type == TMP)
			{
				ft_strdel(&(tmp->tmp_val));
				if (val && val[0] != 26 && !(tmp->tmp_val = ft_strdup(val)))
					return (sh_error(FALSE, 6, NULL, NULL));
				tmp->type += (type == TMP
					&& (tmp->type == ENV || tmp->type == LOCAL) ? TMP : 0);
			}
			else
			{
				ft_strdel(&(tmp->value));
				if (val && val[0] != 26 && !(tmp->value = ft_strdup(val)))
					return (sh_error(FALSE, 6, NULL, NULL));
				tmp->type = type;
			}
			return (TRUE);
		}
		tmp = tmp->next;
	}
	if (ret == FALSE)
		ret = add_env(name, val, type);
	return (ret);
}

static int			exec_cmd_env(int i, int len, char **arg)
{
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
	if ((i = ft_strcmp(arg[0], "env")) == 0
	|| (j = check_builtin(0, cmd, NULL)) != TRUE)
		handle_fork(pipefd_tab, savior_tree(NULL, FALSE), NULL, cmd);
	free_tab(&cmd);
	return (TRUE);
}

int					modif_env(char **arg, int len, int *i, char opt[3][2])
{
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
	del_tmp_env(opt[0][1]);
	return (TRUE);
}

char				*get_env(char *name, t_env type, int all_env)
{
	t_duo				*env;
	char				*tmp;

	tmp = NULL;
	env = savior_env(NULL, FALSE);
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0 &&
		(env->type == type || all_env == TRUE))
		{
			if ((type == ENV || type == LOCAL) && env->value != NULL
			&& ((tmp = ft_strdup(env->value)) == NULL))
				sh_error(FALSE, 6, NULL, NULL);
			else if (env->tmp_val != NULL && !(tmp = ft_strdup(env->tmp_val)))
				sh_error(FALSE, 6, NULL, NULL);
			return (tmp);
		}
		env = env->next;
	}
	return (tmp);
}
