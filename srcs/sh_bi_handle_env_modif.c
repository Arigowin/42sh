#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value, int local)
{
	t_duo				*env;

	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else
		env = savior_env(NULL, FALSE);
	if (name == NULL)
		return (sh_error(TRUE, 26, "setenv", NULL));
	else
	{
		if (value && value[0] == 26)
			duo_pushback(&env, name, "");
		else
			duo_pushback(&env, name, value);
		if (local == TRUE)
			savior_local(env, TRUE);
		else
			savior_env(env, TRUE);
	}
	env = NULL;
	return (TRUE);
}

int					change_env(char *name, char *value, int local)
{
	t_duo				*env;

	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else
		env = savior_env(NULL, FALSE);
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			ft_strdel(&(env->value));
			if (value && value[0] != 26 && !(env->value = ft_strdup(value)))
				return (sh_error(FALSE, 6, NULL, NULL));
			return (TRUE);
		}
		env = env->next;
	}
	add_env(name, value, local);
	env = NULL;
	return (TRUE);
}

char				*get_env(char *name, int local)
{
	t_duo				*env;
	char				*tmp;

	tmp = NULL;
	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else
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
