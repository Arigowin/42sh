#include "shell.h"
#include "libft.h"

static int			add_var_name_in_env(char *str, t_duo **tmp_local,
					t_duo *local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- TOTO --------------------", 2);

	t_duo				*tmp2;
	char				**new_arg;
	char				*name;
	char				*val;
	char				*ret;

	ret = 0;
	new_arg = NULL;
	tmp2 = *tmp_local;
	(void)tmp2;
	(void)local;
	if ((ret = ft_strchr(str, '=')) != NULL)
		new_arg = ft_strsplit(str, '=');
	name = (new_arg ? new_arg[0] : str);
	val = (new_arg ? new_arg[1] : get_env(name, TRUE));
	change_env(name, val, FALSE);
	free_tab(&new_arg);
	del_env(tmp_local, name, TRUE);
	return (TRUE);
}


int					bi_export(char **arg, t_duo **env, const char *opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI EXPORT --------------------", 2);

	int					i;
	t_duo				*local;
	t_duo				*tmp_local;

	i = 0;
	(void)env;
	if (!(arg && *arg && ft_strcmp(arg[0], "export") == 0))
		return (FALSE);
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
	local = savior_local(NULL, FALSE);
	tmp_local = local;
	while (arg[++i])
	{
		add_var_name_in_env(arg[i], &tmp_local, local);
		tmp_local = local;
	}
	return (TRUE);
}
