#include <unistd.h>
#include "shell.h"
#include "libft.h"
#include <stdio.h>
#define cd "LP"
#define env "iu"
#define echo "neE"
#define export "p"

void				print_arg(char **arg)
{
	int i = 0;

	while (arg[i])
	{
		printf(">>> arg[%d] %s\n", i, arg[i]);
		i++;
	}
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
	bi_option[i](arg, curr_opt, arg[0]);
	return (TRUE);
}

static int			bi_opt(char **arg, int *i, int *no_more, const char *handled_opt)
{
//	printf("XXXXXXXXX bi = %s\n", bi);
//	printf("OPTIONS BI DANS BI_OPT = %s\n", handled_opt);
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- BI OPT ------------------", 2);

	int					j;
	char				bi_opt[2];

	j = 1;
	if (*no_more == TRUE)
		return (FALSE);
	if (ft_strcmp("echo", arg[*i]) && arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1] && arg[*i][1] == '-')
		*no_more = TRUE;
	else if (arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		while (arg[*i][j])
		{
			printf(">>> argchar[%d] %c\n", j, arg[*i][j]);
			if (ft_strcmp("echo", arg[0]) == 0
			&& ft_strchr(handled_opt, arg[*i][j]) == NULL)
				return (ERROR);
			else if (ft_strcmp("echo", arg[0])
		   	&& ft_strchr(handled_opt, arg[*i][j]) == NULL)
			{
				bi_opt[0] = arg[*i][j];
				bi_opt[1] = '\0';
				return (sh_error(-2, 22, bi_opt, str_tolower(arg[0])));
			}
			else if (ft_strchr(handled_opt, arg[*i][j]))
				manage_opt(arg, arg[*i][j], handled_opt);
		   		// appeler un poiteur sur fct qui appelle la bonne fct pour la bonne option avec le bon bi
			j++;
		}
	}
	return (TRUE);
}

/*
** *i++ parce que faut tester les options si ils sont separe par des espaces
*/
int					check_opt(char **arg, int *i, const char *opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- CHECK OPT ------------------", 2);

	int					no_more;
	int					ret;
	char				**tmp;

	no_more = FALSE;
	tmp = arg;
//	printf("OPTIONS BI DANS CHECK_OPT = %s\n", opt);
/*
	while (arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		if ((ret = bi_opt(arg[*i], arg[0], &no_more, opt)) != TRUE)
*/
	while (arg && arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
//		printf("arg[%d] = %s\n", *i, arg[*i]);
		if ((ret = bi_opt(arg, i, &no_more, opt)) != TRUE)
			break ;
		(*i)++;
	}
	if (ft_strcmp(arg[0], "echo") == 0 && ret == ERROR)
		arg = tmp;
	if (ret == -2) // -P je rentre dedans
		return (ERROR);
	return (ret);
}
