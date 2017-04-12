#include <unistd.h>
#include "shell.h"
#include "libft.h"

int					del_stline(t_line **stline)
{
	ft_strdel(&((*stline)->line));
	ft_strdel(&((*stline)->curr_hist));
	ft_strdel(&((*stline)->copy.cpy));
	ft_strdel(&((*stline)->copy.bkup));
	ft_strdel(&((*stline)->hrd.line));
	return (TRUE);
}

int					exit_pgm(int exit_code)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- EXIT PGM ------------------", 2);

	t_node				*tree;
	t_line				*stline;
	t_duo				*env;

	tree = savior_tree(NULL, FALSE);
	savior_history(NULL, FALSE);
	stline = savior_stline(NULL, FALSE);
	env = savior_env(NULL, FALSE);
	del_tree(&tree);
	savior_tree(NULL, TRUE);
	save_history();
	duo_del(&env);
	savior_env(NULL, TRUE);
	reset_term();
	del_stline(&stline);
	savior_stline(NULL, TRUE);
	exit(exit_code);
	return (0);
}

int					bi_exit(char **arg, char opt[3][2])
{
	int					i;

	i = 0;
	(void)opt;
	if (arg && arg[1] && arg[2])
		return (sh_error(FALSE, 27, NULL, NULL));
	while (arg && arg[1] && arg[1][i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
			return (sh_error(FALSE, 28, arg[1], NULL));
		i++;
	}
	i = (arg && arg[1] ? ft_atoi(arg[1]) : 0);
	free_tab(&arg);
	ft_putendl("exit");
	exit_pgm(i);
	return (0);
}
