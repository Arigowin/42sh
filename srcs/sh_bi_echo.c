#include "shell.h"
#include "libft.h"

int					bi_echo(char **arg, t_duo **env, const char *opt)
{
	int i;

	i = 1;
	(void)env;
	check_opt(arg, &i, opt);
	if (tbl_len(arg) > 1)
	{
		while (arg && arg[i])
		{
			ft_putstr_visible(arg[i]);
			if (arg[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	ft_putchar('\n');
	return (TRUE);
}
