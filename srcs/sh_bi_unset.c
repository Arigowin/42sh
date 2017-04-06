#include "shell.h"
#include "libft.h"

int					bi_unset(char **arg, t_duo **env, const char *opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI UNSET ------------------", 2);

	int					ret;
	int					i;
	t_duo				*env_tmp;

	i = 1;
	(void)env;
	check_opt(arg, &i, opt, 0);
	env_tmp = savior_env(NULL, FALSE);
	while (arg[i])
	{
		if ((ret = del_env(&env_tmp, arg[i], FALSE)) == -1)
		{
			env_tmp = savior_local(NULL, FALSE);
			if ((ret = del_env(&env_tmp, arg[i], TRUE)) == -1)
				sh_error(TRUE, 14, arg[i], NULL);
		}
		i++;
	}
	return (TRUE);
}
