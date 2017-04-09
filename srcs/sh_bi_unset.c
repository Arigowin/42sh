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

int					unset_check_env(char *name, char opt[3][2], int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET CHECK ENV ------------------", 2);

	t_duo				*env_tmp;
	char				*value;
	int					fct;

	value = get_env(name, local);
	if (local == TRUE)
		env_tmp = savior_local(NULL, FALSE);
	else
		env_tmp = savior_env(NULL, FALSE);
	fct = check_env_fct(value);
	if ((opt[0][1] == 1 && fct == FALSE) || (opt[1][1] == 1 && fct == TRUE) ||
	opt[0][1] == opt[1][1])
		return (del_env(&env_tmp, name, local));
	else if ((opt[0][1] == 1 && fct == TRUE) || (opt[1][1] == 1 && fct == FALSE))
		return (sh_error(ERROR, 34, NULL, NULL));
	return (FALSE);
}

int					bi_unset(char **arg, t_duo **env, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI UNSET ------------------", 2);

	int					local;
	int					ret;
	int					i;

	(void)env;
	i = 1;
	ret = check_opt(arg, &i, opt);
	if (!arg[i])
		sh_error(FALSE, 9, NULL, arg[0]);
	local = (get_env(arg[i], TRUE) ? TRUE : FALSE);
	while (ret != ERROR && arg[i])
	{
		if ((ret = unset_check_env(arg[i], opt, local)) == ERROR)
			break ;
		else if (ret == FALSE)
			sh_error(TRUE, 14, arg[i], arg[0]);
		i++;
	}
	return (TRUE);
}
