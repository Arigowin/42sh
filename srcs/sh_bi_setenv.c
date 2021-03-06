/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bi_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:54 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:40:41 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include "libft.h"

int					valid_env_name(char *str, char *bi)
{
	int					i;

	i = -1;
	if (str && str[++i] != '_' && ft_isalpha(str[i]) == FALSE)
		return (sh_error(FALSE, 15, str, bi));
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '.' && ft_isalnum(str[i]) == FALSE)
			return (sh_error(FALSE, 15, str, bi));
		i++;
	}
	return (TRUE);
}

int					bi_setenv(char **arg, char opt[3][2])
{
	int					i;

	i = 0;
	while (arg[i])
	{
		if (i == 1 && valid_env_name(arg[i], arg[0]) == FALSE)
			return (FALSE);
		i++;
	}
	if (i < 2)
		return (bi_env(arg, opt));
	if (i == 2 || i == 3)
	{
		del_env(arg[1]);
		change_env(arg[1], arg[2], ENV);
		return (TRUE);
	}
	if (i > 3)
		return (sh_error(FALSE, 10, NULL, NULL));
	return (TRUE);
}
