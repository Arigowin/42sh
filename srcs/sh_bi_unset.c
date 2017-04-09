#include "shell.h"
#include "libft.h"

int					check_env_fct(char *value)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK ENV FCT ------------------", 2);

	char				*tmp;
	int					i;

	if (value == NULL)
		return (FALSE);
	tmp = str_trim_all(value);
	if (tmp[0] == '(')
	{
		i = 0;
		while (tmp[++i] != ')')
			if (!ft_isprint(tmp[i]))
				return (FALSE);
		if (tmp[i + 1] == '{')
		{
			while (tmp[++i] != '}')
				if (!ft_isprint(tmp[i]))
					return (FALSE);
			if (tmp[i - 1] == ';' && !tmp[i + 1])
				return (TRUE);
		}
	}
	return (FALSE);
}

int					unset_check_env(char *name, int fct, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET CHECK ENV ------------------", 2);

	t_duo				*env_tmp;
	char				*value;

	if ((value = get_env(name, local)))
	{
		if (check_env_fct(value) == fct)
		{
			if (local == FALSE)
				env_tmp = savior_env(NULL, FALSE);
			else
				env_tmp = savior_local(NULL, FALSE);
			del_env(&env_tmp, value, FALSE);
			return (TRUE);
		}
		return (ERROR);
	}
	return (FALSE);
}

int					bi_unset(char **arg, t_duo **env, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI UNSET ------------------", 2);

	int					ret;
	int					i;
	t_duo				*env_tmp;

	i = 1;
	ret = check_opt(arg, &i, opt);
	if (!arg[i])
		sh_error(FALSE, 9, NULL, arg[0]);
	env_tmp = *env;
	while (ret != ERROR && arg[i])
	{
		if (arg[i][0] != '-' && (del_env(&env_tmp, arg[i], FALSE)) == -1)
		{
			env_tmp = savior_local(NULL, FALSE);
			if (arg[i][0] != '-' && (del_env(&env_tmp, arg[i], TRUE)) == -1)
				sh_error(TRUE, 14, arg[i], arg[0]);
		}
		i++;
	}
	return (TRUE);
}
