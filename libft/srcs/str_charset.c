/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_charset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:27:21 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:27:23 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int					str_charset(char **str, char c, int start, int end)
{
	int					i;

	i = start;
	if (str == NULL || *str == NULL || start > end)
		return (0);
	while ((*str)[i] && i < end)
	{
		(*str)[i] = c;
		i++;
	}
	return (1);
}
