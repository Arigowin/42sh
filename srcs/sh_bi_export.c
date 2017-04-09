#include "shell.h"
#include "libft.h"

static int			add_var_name_in_env(char *str, t_duo **tmp_local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- ADD VAR NAME +++ --------------------", 2);

	char				**new_arg;
	char				*name;
	char				*val;
	char				*ret;

	ret = 0;
	new_arg = NULL;
	if ((ret = ft_strchr(str, '=')) != NULL)
		new_arg = ft_strsplit(str, '=');
	name = (new_arg ? new_arg[0] : str);
	val = (new_arg ? new_arg[1] : get_env(name, TRUE));
	change_env(name, val, FALSE);
	free_tab(&new_arg);
	del_env(tmp_local, name, TRUE);
	return (TRUE);
}

int					export_p(char **arg, int i)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- EXPORT P --------------------", 2);

	int					ret;
	t_duo				*env;

	i = 1;
	ret = TRUE;
	while (arg && arg[i] && arg[i][0] && arg[i][0] == '-')
		i++;
	if (arg[i])
		return (sh_error(FALSE, 36, arg[i], NULL));
	env = savior_env(NULL, FALSE);
	while (env)
	{
		ret = 2;
		ft_putstr("export ");
		ft_putstr(env->name);
		ft_putstr("=\"");
		ft_putstr(env->value);
		ft_putendl("\"");
		env = env->next;
	}
	return (ret);
}


int					bi_export(char **arg, t_duo **env, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI EXPORT --------------------", 2);

	int					i;
	t_duo				*local;
	t_duo				*tmp_local;

	i = 1;
	(void)env;
	if (!(arg && *arg && ft_strcmp(arg[0], "export") == 0))
		return (FALSE);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	if (opt[0][1] == 1 && export_p(arg, i))
		return (FALSE);
	local = savior_local(NULL, FALSE);
	tmp_local = local;
	while (arg[i])
	{
		if (arg[i][0] != '-')
			add_var_name_in_env(arg[i], &tmp_local);
		tmp_local = local;
		i++;
	}
	return (TRUE);
}
