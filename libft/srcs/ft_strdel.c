/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:33:50 by avacher           #+#    #+#             */
/*   Updated: 2015/11/30 14:24:24 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strdel(char **as)
{
#include <stdio.h>
	if (as && *as)
	{
		printf("-----------adresse ((%s))-------- 1\n", *as);//, *as, *as);
		ft_bzero(*as, ft_strlen(*as));
		free(*as);
		*as = NULL;
		printf("-----------adresse ((%p))-------- 1\n", *as);//, *as, *as);
	}
}
