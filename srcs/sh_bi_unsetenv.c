#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			del_first(t_duo **env, char *name, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- DEL FIRST ------------------", 2);

	t_duo				*tmp;

	tmp = *env;
	if (name && env && *env && ft_strcmp(name, (*env)->name) == 0)
	{
		*env =(*env)->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		free(tmp);
		tmp = NULL;
		if (local == TRUE)
			savior_local(*env, TRUE);
		else if (local == FALSE)
			savior_env(*env, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

int					del_env(t_duo **env, char *name, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- DEL ENV ------------------", 2);

	t_duo				*cpy;
	t_duo				*tmp;

	if (del_first(env, name, local) == TRUE)
		return (TRUE);
	cpy = *env;
	tmp = NULL;
	while (cpy && cpy->next)
	{
		if (ft_strcmp(name, cpy->next->name) == 0)
		{
			tmp = cpy->next->next;
			ft_strdel(&(cpy->next->name));
			ft_strdel(&(cpy->next->value));
			free(cpy->next);
			cpy->next = tmp;
			if (local == TRUE)
				savior_local(*env, TRUE);
			else if (local == FALSE)
				savior_env(*env, TRUE);
			return (TRUE);
		}
		cpy = cpy->next;
	}
	return (FALSE);
}

int					bi_unsetenv(char **arg, t_duo **env, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSETENV ------------------", 2);

	int					i;

	i = 1;
	(void)opt;
	if (!arg[i])
		sh_error(FALSE, 9, NULL, arg[0]);
	while (arg[i])
	{
		if (del_env(env, arg[i], FALSE) == FALSE)
			sh_error(TRUE, 14, arg[i], arg[0]);
		i++;
	}
	return (0);
}
