/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:08:17 by avacher           #+#    #+#             */
/*   Updated: 2015/11/29 15:02:45 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*str_trim_all(char *s)
{
	char		*str;
	int			i;
	int			j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	str = ft_strnew(ft_strlen(s));
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
			i++;
		str[j] = s[i];
		i++;
		j++;
	}
	ft_strdel(&s);
	return (str);
}
