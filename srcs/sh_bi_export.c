#include <unistd.h>
#include "shell.h"
#include "libft.h"

int					toto(char *str, int local)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- TOTO --------------------", 2);

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
	change_env(name, val, local);
	free_tab(&new_arg);
	return (TRUE);
}


int					bi_export(char **arg, t_duo **env)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI EXPORT --------------------", 2);

	int					i;
	t_duo				*local;
	t_duo				*tmp_local;

	i = 0;
	(void)env;
	local = savior_local(NULL, FALSE);
	tmp_local = local;
	if (!(arg && *arg && ft_strcmp(arg[0], "export") == 0))
		return (FALSE);
	while (arg[++i])
	{
		toto(arg[i], FALSE);
		while (!ft_strchr(arg[i], '=') && tmp_local && tmp_local->next)
		{
			if (ft_strcmp(tmp_local->next->name, arg[i]) == 0)
			{
				free_tduo_link(&tmp_local);
				savior_local(local, TRUE);
			}
			tmp_local = tmp_local->next;
		}
		tmp_local = local;
	}
	return (TRUE);
}
