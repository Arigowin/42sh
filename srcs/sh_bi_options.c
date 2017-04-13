/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bi_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:54 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:15:24 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include "libft.h"

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
			opt[i][1] = 1;
			return (TRUE);
		}
		i++;
	}
	return (ERROR);
}

static int			bi_opt(char **arg, int i, char handled_opt[3][2])
{
	int					j;

	if (arg[i] && arg[i][0] && arg[i][0] == '-' && arg[i][1])
	{
		j = 1;
		while (arg[i][j])
		{
			if (set_opt(arg[0], handled_opt, arg[i][j]) == ERROR)
			{
				if (ft_strcmp("echo", arg[0]) == 0)
					return (2);
				bi_usage(arg[0], arg[i][j], handled_opt);
				return (ERROR);
			}
			j++;
		}
	}
	return (TRUE);
}

int					check_opt(char **arg, int *i, char opt[3][2])
{
	int					no_more;
	int					ret;
	char				**tmp;

	no_more = FALSE;
	tmp = arg;
	ret = TRUE;
	while (arg && arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1])
	{
		if (no_more == TRUE)
			return (FALSE);
		if (arg[*i] && arg[*i][0] && arg[*i][0] == '-' && arg[*i][1]
		&& arg[*i][1] == '-')
			no_more = TRUE;
		else if ((ret = bi_opt(arg, *i, opt)) != TRUE)
			break ;
		(*i)++;
	}
	if (ft_strcmp(arg[0], "echo") == 0 && ret == FALSE)
		arg = tmp;
	return (ret);
}
