#include <unistd.h>
#include "shell.h"
#include "libft.h"

static int			bi_opt(char *arg, char *bi, int *no_more, char *handled_opt)
{
	int					i;

	i = 1;
	if (*no_more == TRUE)
		return (FALSE);
	if (ft_strcmp("echo", bi) && arg
	&& arg[0] && arg[0] == '-' && arg[1] && arg[1] == '-')
		*no_more = TRUE;
	else if (arg && arg[0] && arg[0] == '-' && arg[1])
	{
		while (arg[i])
		{
			if (ft_strcmp("echo", bi) == 0
			&& ft_strchr(handled_opt, arg[i]) == NULL)
				return (ERROR);
			else if (ft_strcmp("echo", bi)
		   	&& ft_strchr(handled_opt, arg[i]) == NULL)
				return (sh_error(-2, 22, &arg[i], bi));
//			else
		   		// appeler un poiteur sur fct qui appelle la bonne fct pour la bonne option avec le bon bi
			i++;
		}
	}
	return (TRUE);
}

int					check_opt(char **arg, int *i)
{
	int					no_more;
	int					ret;
	char				*opt_list;
	char				**tmp;

	no_more = FALSE;
	tmp = arg;
	opt_list = str_toupper(arg[0]);
	while (arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		if ((ret = bi_opt(arg[*i], arg[0], &no_more, opt_list)) != TRUE)
			break ;
		(*i)++;
	}
	if (ft_strcmp(arg[0], "echo") == 0 && ret == ERROR)
		arg = tmp;
	if (ret == -2)
		return (ERROR);
	return (ret);
}
