#include "shell.h"
#include "libft.h"

int					check_env_fct(char *value)
{
	if (DEBUG_BI == 0)
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

int					unset_opt(char **arg, int fct, char opt, char *oth_opt)
{
	static char			err_msg[8] = {'u', 'n', 's', 'e', 't', ' ', '-',' '};
	int					i;
	int					j;
	int					ret;

	i = 0;
	ret = TRUE;
	while (arg && arg[i] && arg[i][0] == '-')
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] != *oth_opt)
			{printf("la on passe? P\n");
				*oth_opt = arg[i][j];
				return (2);
			}
			if (arg[i][j] == *oth_opt)
			{printf("la on passe? P2\n");
				*oth_opt = arg[i][j];
				return (4);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (arg[++i])
	{
		if (arg[i][0] != '-')
		{
			if ((ret = unset_check_env(arg[i], fct, FALSE)) == FALSE)
				ret = unset_check_env(arg[i], fct, TRUE);
			if (ret == ERROR)
			{
				err_msg[7] = opt;
				sh_error(ERROR, 34, arg[i], err_msg);
			}
		}
	}
	return (ret);
}

int					unset_v(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 0)
		ft_putendl_fd("----------------------- UNSET V ------------------", 2);

	static char			oth_opt = 'v';
	int 				fct;
	int					ret;

	(void)bi;
	if (oth_opt != 'v')
		return (2);
	fct = FALSE;
	ret = unset_opt(arg, fct, curr_opt, &oth_opt);
	return (ret);
}

int					unset_f(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 0)
		ft_putendl_fd("----------------------- UNSET F ------------------", 2);

	static char			oth_opt = 'f';
	int 				fct;
	int					ret;

	(void)bi;
	if (oth_opt != 'f')
		return (2);
	fct = TRUE;
	ret = unset_opt(arg, fct, curr_opt, &oth_opt);
	return (ret);
}

int					bi_unset(char **arg, t_duo **env, const char *opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI UNSET ------------------", 2);

	int					ret;
	int					i;
	t_duo				*env_tmp;

	(void)env;
	i = 1;
	ret = check_opt(arg, &i, opt);
	if (!arg[i])
		sh_error(FALSE, 9, NULL, arg[0]);
	env_tmp = savior_env(NULL, FALSE);
	while (ret != ERROR && arg[i])
	{
		if ((del_env(&env_tmp, arg[i], FALSE)) == -1)
		{
			env_tmp = savior_local(NULL, FALSE);
			if (arg[i][0] != '-' && (del_env(&env_tmp, arg[i], TRUE)) == -1)
				sh_error(TRUE, 14, arg[i], arg[0]);
		}
		i++;
	}
	return (TRUE);
}
