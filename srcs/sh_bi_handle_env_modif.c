#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value, t_env type)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD ENV ------------------", 2);

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
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHANGE ENV ------------------", 2);

	t_duo				*tmp;
	char				**toto;
	int					ret;

	ret = FALSE;
	tmp = savior_env(NULL, FALSE);
	while (tmp)
	{
		if (tmp && name && ft_strcmp(tmp->name, name) == 0)
		{
			toto = (type == TMP ? &(tmp->tmp_val) : &(tmp->value));
			ft_strdel(toto);
			if (val && val[0] != 26 && !(*toto = ft_strdup(val)))
				return (sh_error(FALSE, 6, NULL, NULL));
			tmp->type += (type == TMP && (tmp->type == ENV
						|| tmp->type == LOCAL) ? TMP : 0);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	if (ret == FALSE)
		ret = add_env(name, val, type);
	return (ret);
}

char				*get_env(char *name, t_env type, int all_env)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- GET ENV ------------------", 2);

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
