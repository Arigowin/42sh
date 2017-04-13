#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			del_first(t_duo **env, char *name)
{
	t_duo				*tmp;

	tmp = *env;
	if (name && env && *env && ft_strcmp(name, (*env)->name) == 0)
	{
		*env = (*env)->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		ft_strdel(&(tmp->tmp_val));
		free(tmp);
		tmp = NULL;
		savior_env(*env, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

int					del_env(char *name)
{
	t_duo				*env;
	t_duo				*cpy;
	t_duo				*tmp;

	env = savior_env(NULL, FALSE);
	cpy = env;
	if (del_first(&env, name) == TRUE)
		return (TRUE);
	tmp = NULL;
	while (cpy && cpy->next)
	{
		if (ft_strcmp(name, cpy->next->name) == 0)
		{
			tmp = cpy->next->next;
			ft_strdel(&(cpy->next->name));
			ft_strdel(&(cpy->next->value));
			ft_strdel(&(cpy->next->tmp_val));
			free(cpy->next);
			cpy->next = tmp;
			savior_env(env, TRUE);
			return (TRUE);
		}
		cpy = cpy->next;
	}
	return (FALSE);
}

int					bi_unsetenv(char **arg, char opt[3][2])
{
	int					i;

	i = 1;
	(void)opt;
	if (!arg[i])
		sh_error(FALSE, 9, NULL, arg[0]);
	while (arg[i])
	{
		if (del_env(arg[i]) == FALSE)
			sh_error(TRUE, 14, arg[i], arg[0]);
		i++;
	}
	return (0);
}
