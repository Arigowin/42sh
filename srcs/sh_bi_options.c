#include <unistd.h>
#include "shell.h"
#include "libft.h"
#define cd "LP"
#define env "iu"
#define echo "neE"
#define export "p"

static char			*concat_to_str(char opt[3][2])
{
	char				*str;
	int					i;

	i = 0;
	if ((str = ft_strnew(4)) == NULL)
		sh_error(FALSE, 6, NULL, NULL);
	while (i < 3)
	{
		str[i] = opt[i][0];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int			bi_usage(char *bi, char curr_opt, char handled_opt[3][2])
{
	char				*str;

	str = concat_to_str(handled_opt);
	ft_putstr("42sh: ");
	ft_putstr(bi);
	ft_putstr(": '");
	ft_putchar(curr_opt);
	ft_putendl("': invalid option");
	ft_putstr(bi);
	ft_putstr(": usage: ");
	ft_putstr(bi);
	ft_putstr(" [-");
	ft_putstr(str);
	ft_strdel(&str);
	ft_putstr("] [");
	if (ft_strcmp(bi, "cd") == 0)
		ft_putstr("dir");
	if (ft_strcmp(bi, "env") == 0)
		ft_putstr("exec");
	if (ft_strcmp(bi, "export") == 0)
		ft_putstr("name[=value]");
	if (ft_strcmp(bi, "unset") == 0)
		ft_putstr("name");
	ft_putendl("]");
	return(ERROR);
}

int					keep_last_opt(char opt[3][2], char curr_opt, int i)
{
	if (curr_opt == 'e' || curr_opt == 'L')
	{
		opt[i][1] = 1;
		opt[i + 1][1] = 0;
	}
	else if (curr_opt == 'E' || curr_opt == 'P')
	{
		opt[i][1] = 0;
		opt[i + 1][1] = 1;
	}
	return (TRUE);
}

int					set_opt(char *bi, char opt[3][2], char curr_opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- SET OPT ------------------", 2);

	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (opt[i][0] == curr_opt && opt[i][0] != 'n'
		&& (ft_strcmp("echo", bi) == 0 || ft_strcmp("cd", bi) == 0))
		{
			j = (ft_strcmp("echo", bi) == 0 ? 1 : 0);
			keep_last_opt(opt, curr_opt, j);
			return (TRUE);
		}
		else if (opt[i][0] == curr_opt)
		{
			opt[i][1] =  1;
			return (TRUE);
		}
		i++;
	}
	return (ERROR);
}

static int			bi_opt(char **arg, int i, char handled_opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI OPT ------------------", 2);

	int					j;
	int					ret;

	j = 1;
	ret = TRUE;
	if (arg[i] && arg[i][0] && arg[i][0] == '-' && arg[i][1])
	{
		while (arg[i][j])
		{
			if (ft_strcmp("echo", arg[0]) && (ret = set_opt(arg[0], handled_opt,
			arg[i][j])) == ERROR)
				return (bi_usage(arg[0], arg[i][j], handled_opt));
			j++;
		}
	}
	return (TRUE);
}

int					check_opt(char **arg, int *i, char opt[3][2])
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK OPT ------------------", 2);

	int					no_more;
	int					ret;
	char				**tmp;

	no_more = FALSE;
	tmp = arg;
	ret = FALSE;
	while (arg && arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		if (no_more == TRUE)
			return (FALSE);
		if (ft_strcmp("echo", arg[*i]) && arg[*i] && arg[*i][0]
		&& arg[*i][0] == '-' && arg[*i][1] && arg[*i][1] == '-')
			no_more = TRUE;
		if ((ret = bi_opt(arg, *i, opt)) != TRUE)
			break ;
		(*i)++;
	}
	if (ft_strcmp(arg[0], "echo") == 0 && ret == ERROR)
		arg = tmp;
	if (ret == -2)
		return (ERROR);
	return (ret);
}
