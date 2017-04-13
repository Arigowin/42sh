/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tduo_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:25:14 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:25:36 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					free_tduo_link(t_duo **lst)
{
	t_duo				*tmp;

	tmp = NULL;
	if (lst == NULL)
		return (-1);
	tmp = (*lst)->next;
	ft_strdel(&((*lst)->name));
	ft_strdel(&((*lst)->value));
	ft_strdel(&((*lst)->tmp_val));
	free(*lst);
	*lst = tmp;
	tmp = NULL;
	return (0);
}
