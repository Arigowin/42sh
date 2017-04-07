#include <unistd.h>
#include "shell.h"
#include "libft.h"
#define cd "LP"
#define env "iu"
#define echo "neE"
#define export "p"

static int			bi_usage(char *bi, char curr_opt, const char *handled_opt)
{
	ft_putstr("42sh: ");
	ft_putstr(bi);
	ft_putstr(": '");
	ft_putchar(curr_opt);
	ft_putendl("': invalid option");
	ft_putstr(bi);
	ft_putstr(": usage: ");
	ft_putstr(bi);
	ft_putstr(" [-");
	ft_putstr(handled_opt);
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

int					manage_opt(char **arg,char curr_opt, const char *options)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- MANAGE OPT ------------------", 2);

	int					i;
	char				*tmp;
	char				*join_bi_opt;
	static char			*opt_bi[] = {"cd_L", "cd_P",
						"echo_n", "env_i", "export_p", "unset_f", "unset_v"};
	static int			(*bi_option[])(char **arg, char curr_opt, char *bi) =
						{&cd_L, &cd_P, &echo_n, &env_i, &export_p, &unset_f,
						&unset_v};
	(void)options;
	i = 0;
	tmp = ft_strjoin(arg[0], "_");
	join_bi_opt = ft_strnew(ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		join_bi_opt[i] = tmp[i];
		i++;
	}
	join_bi_opt[i] = curr_opt;
	i = 0;
	while (i < 7 && ft_strcmp(opt_bi[i], join_bi_opt) != 0)
		i++;
	int ret = bi_option[i](arg, curr_opt, arg[0]);
	return (ret);
}

static int			bi_opt(char **arg, int i, const char *handled_opt)
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
			if (ft_strcmp("echo", arg[0]) == 0
			&& ft_strchr(handled_opt, arg[i][j]) == NULL)
				return (ERROR);
			else if (ft_strcmp("echo", arg[0])
		   	&& ft_strchr(handled_opt, arg[i][j]) == NULL)
				return (bi_usage(arg[0], arg[i][j], handled_opt));
			else if (ft_strchr(handled_opt, arg[i][j])
			&& (ret =  manage_opt(arg, arg[i][j], handled_opt)) == 2)
				return (2);
			j++;
		}
	}
	return (ret);
}

int					check_opt(char **arg, int *i, const char *opt)
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
