/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 21:03:57 by avacher           #+#    #+#             */
/*   Updated: 2015/12/12 12:10:52 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_isstrascii(char *str)
{
	int					i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (ft_isascii(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
