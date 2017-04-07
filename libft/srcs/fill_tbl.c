/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:49:05 by avacher           #+#    #+#             */
/*   Updated: 2016/01/13 19:32:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*fill_tbl(char *str, char c)
{
	char			*tmp;
	int				i;

	i = 0;
	if ((tmp = ft_strnew(ft_strlen(str) + 2)) == NULL)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[++i] = '\0';
	return (tmp);
}
