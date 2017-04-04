#include <unistd.h>
#include "shell.h"
#include "libft.h"
#define cd "LP"
#define env "iu"
#define echo "neE"
#define export "p"

int					manage_opt(char curr_opt, char *bi, const char *options)
{
	(void)curr_opt;
	(void)bi;
	(void)options;

	return (TRUE);
}

static int			bi_opt(char *arg, char *bi, int *no_more, const char *handled_opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI OPT ------------------", 2);
	int					i;
	char				bi_opt[2];

	i = 1;
				printf("TROLOLO!!!!! ((%s))\n", handled_opt);
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
			{
				bi_opt[0] = arg[i];
				bi_opt[1] = '\0';
				return (sh_error(-2, 22, bi_opt, str_tolower(bi)));
			}
			else if (ft_strchr(handled_opt, arg[i]))
				manage_opt(arg[i], bi, handled_opt);
		   		// appeler un poiteur sur fct qui appelle la bonne fct pour la bonne option avec le bon bi
			i++;
		}
	}
	return (TRUE);
}

int					check_opt(char **arg, int *i, const char *opt)
{
	int					no_more;
	int					ret;
	char				**tmp;

	no_more = FALSE;
	tmp = arg;
				printf("TROLOLO!!!!! ((%s))\n", opt);
	while (arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		if ((ret = bi_opt(arg[*i], arg[0], &no_more, opt)) != TRUE)
			break ;
		(*i)++;
	}
	if (ft_strcmp(arg[0], "echo") == 0 && ret == ERROR)
		arg = tmp;
	if (ret == -2)
		return (ERROR);
	return (ret);
}
