#include "shell.h"
#include "libft.h"

static int			add_var_name_in_env(char *str, int opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD VAR NAME +++ --------------------", 2);

	char				**new_arg;
	char				*name;
	char				*val;
	char				*ret;
	int					env;

	ret = 0;
	new_arg = NULL;
	if ((ret = ft_strchr(str, '=')) != NULL)
		new_arg = ft_strsplit(str, '=');
	name = (new_arg ? new_arg[0] : str);
	val = (new_arg ? ft_strdup(new_arg[1]) : get_env(name, LOCAL, TRUE));
	if (!valid_env_name(name, "export"))
		return (FALSE);
	if (!val)
	{
		free_tab(&new_arg);
		return (sh_error(FALSE, 14, name, "export"));
	}
	del_env(name);
	env = (opt == 1 ? LOCAL : ENV);
	change_env(name, val, env);
	free_tab(&new_arg);
	ft_strdel(&val);
	return (TRUE);
}

static void			print_export_p(char *curr_opt, char *name, char *value)
{
		ft_putstr("export ");
		ft_putstr(curr_opt);
		ft_putstr(name);
		ft_putstr("=\"");
		ft_putstr(value);
		ft_putendl("\"");
}

static int			export_p(char **arg, int i, char *curr_opt)
{
	//if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- EXPORT P --------------------", 2);

	t_duo				*env;
	char				*val;
	int					ret;

	ret = TRUE;
	if (!(arg[i]))
	{
		ret = 2;
		env = savior_env(NULL, FALSE);
		while (env)
		{
			val = (env->tmp_val ? env->tmp_val : env->value);
			print_export_p(curr_opt, env->name, val);
			env = env->next;
		}
	}
	while (arg[i])
	{
		if ((val = get_env(arg[i], ENV, TRUE)) != NULL)
			print_export_p(curr_opt, arg[i], val);
		ft_strdel(&val);
		i++;
	}
	return (ret);
}


int					bi_export(char **arg, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI EXPORT --------------------", 2);

	int					i;
	char 				*curr_opt;

	i = 1;
	if (!(arg && *arg && ft_strcmp(arg[0], "export") == 0))
		return (FALSE);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	curr_opt = (arg[1] ? ft_strdup("-p ") : NULL);
	if ((opt[0][1] == 1 || !arg[1]) && export_p(arg, i, curr_opt) != TRUE)
		return (str_dbltbl_ret(FALSE, &curr_opt, NULL, NULL));
	ft_strdel(&curr_opt);
	while (arg[i])
	{
		if (arg[i][0] != '-')
			add_var_name_in_env(arg[i], opt[0][1]);
		i++;
	}
	return (TRUE);
}
