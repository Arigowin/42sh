#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD ENV ------------------", 2);

	t_duo 				*env;

	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else if (local == FALSE)
		env = savior_env(NULL, FALSE);
//	printf("name = %s\n", name);
	if (name == NULL)
		return (sh_error(TRUE, 26, "setenv", NULL));
	if (value && value[0] == 26)
		duo_pushback(&env, name, "");
	else
		duo_pushback(&env, name, value);
	if (local == TRUE)
		savior_local(env, TRUE);
	else if (local == FALSE)
		 savior_env(env, TRUE);
	return (TRUE);
}

int					change_env(char *name, char *value, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHANGE ENV ------------------", 2);

	t_duo				*tmp;

	tmp = NULL;
	if (local == TRUE)
		tmp = savior_local(NULL, FALSE);
	else if (local == FALSE)
		tmp = savior_env(NULL, FALSE);
	while (tmp)
	{
		if (tmp && name && ft_strcmp(tmp->name, name) == 0)
		{
			ft_strdel(&(tmp->value));
			if (value && value[0] != 26 && !(tmp->value = ft_strdup(value)))
				return (sh_error(FALSE, 6, NULL, NULL));
			return (TRUE);
		}
		tmp = tmp->next;
	}
	add_env(name, value, local);
	return (TRUE);
}

char				*get_env(char *name, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- GET ENV ------------------", 2);

	t_duo				*env;
	char				*tmp;

	tmp = NULL;
	env = NULL;
	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else if (local == FALSE)
		env = savior_env(NULL, FALSE);
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			if (env->value != NULL && ((tmp = ft_strdup(env->value)) == NULL))
				sh_error(FALSE, 6, NULL, NULL);
			return (tmp);
		}
		env = env->next;
	}
	return (NULL);
}

int					modif_env(char **arg, t_duo *env, int len, int i)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- MODIF ENV ------------------", 2);

	int					nb;

	nb = 0;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '=') != NULL)
			format_env(arg[i], &nb);
		else
			break ;
		i++;
	}
	if (i < len)
		exec_cmd_env(i, len, arg);
	else
		print_env(env);
	duo_del(&env);
	return (TRUE);
}
