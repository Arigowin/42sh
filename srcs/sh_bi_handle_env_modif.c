#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD ENV ------------------", 2);

	t_duo				*env;

	env = savior_env(NULL, FALSE);
	if (name == NULL)
		return (sh_error(TRUE, 26, "setenv", NULL));
	else
	{
		if (value && value[0] == 26)
			duo_pushback(&env, name, "");
		else
			duo_pushback(&env, name, value);
		savior_env(env, TRUE);
	}
	return (TRUE);
}

int					change_env(char *name, char *value, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHANGE ENV ------------------", 2);

	t_duo				*env;

	env = savior_env(NULL, FALSE);
	(void)local;
	while (env)
	{
	printf("toto trololo -- 1 env ((%s)) name ((%s))\n", env->name, name);
		if (env && name && ft_strcmp(env->name, name) == 0)
		{
	printf("toto trololo -- 2\n");
			ft_strdel(&(env->value));
			if (value && value[0] != 26 && !(env->value = ft_strdup(value)))
				return (sh_error(FALSE, 6, NULL, NULL));
			return (TRUE);
		}
	printf("toto trololo -- 3\n");
		env = env->next;
	printf("toto trololo -- 4\n");
	}
	add_env(name, value);
	return (TRUE);
}

char				*get_env(char *name, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- GET ENV ------------------", 2);

	t_duo				*env;
	char				*tmp;

	(void)local;
	tmp = NULL;
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
