#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			add_env(char *name, char *value, int local, t_duo **env)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD ENV ------------------", 2);

	t_duo 				*tmp;

	tmp = *env;
	if (name == NULL)
		return (sh_error(TRUE, 26, "setenv", NULL));
	while (tmp)
		tmp = tmp->next;
	if (value && value[0] == 26)
		duo_pushback(&tmp, name, "");
	else
		duo_pushback(&tmp, name, value);
	if (local == TRUE)
	{
//		printf("************local\n");
		savior_local(*env, TRUE);
	}
	else if (local == FALSE)
	{
//		printf("****************env\n");
		 savior_env(*env, TRUE);
	}
	return (TRUE);
}

int					change_env(char *name, char *value, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHANGE ENV ------------------", 2);

	t_duo				*env;
	t_duo				*head;

	env = NULL;
	//printf("DANS CHANGE ENV {{{{{{%d}}}}}}\n", local);
	if (local == TRUE)
		env = savior_local(NULL, FALSE);
	else if (local == FALSE)
		env = savior_env(NULL, FALSE);
	head = env;
	while (env)
	{
	//printf("toto trololo -- 1 env ((%s)) name ((%s))\n", env->name, name);
		if (env && name && ft_strcmp(env->name, name) == 0)
		{
	//printf("toto trololo -- 2\n");
			ft_strdel(&(env->value));
			if (value && value[0] != 26 && !(env->value = ft_strdup(value)))
				return (sh_error(FALSE, 6, NULL, NULL));
			return (TRUE);
		}
	//printf("toto trololo -- 3\n");
		env = env->next;
	//printf("toto trololo -- 4\n");
	}
	add_env(name, value, local, &head);


	//t_duo *toto = head;
	//while (toto)
	//{
	//printf("name ap add env [[%s]]\n", toto->name);
	//toto = toto->next;
	//}




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
