#include <unistd.h>
#include "shell.h"
#include "libft.h"

int					valid_env_name(char *str, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- VALID ENV NAME --------------------", 2);

	int					i;

	i = -1;
	if (str && str[++i] != '_' && ft_isalpha(str[i]) == FALSE)
			return (sh_error(FALSE, 15, str, bi));
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '.' && ft_isalnum(str[i]) == FALSE)
			return (sh_error(FALSE, 15, str, bi));
		i++;
	}
	return (TRUE);
}

int					bi_setenv(char **arg, t_duo **env, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI SETENV --------------------", 2);

	int					i;
	t_duo				*env_tmp;

	i = 0;
	(void)opt;
	while (arg[i])
	{
		if (i == 1 && valid_env_name(arg[i], arg[0]) == FALSE)
			return (FALSE);
		i++;
	}
	if (i < 2)
		return (bi_env(arg, env, opt));
	if (i == 2 || i == 3)
	{
		env_tmp = savior_local(NULL, FALSE);
		change_env(arg[1], arg[2], FALSE);
		del_env(&env_tmp, arg[1], TRUE);
		return (TRUE);
	}
	if (i > 3)
		return (sh_error(FALSE, 10, NULL, NULL));
	return (TRUE);
}
