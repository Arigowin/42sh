/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basiclstfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:26:16 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:26:17 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_basiclstfree(t_basic_list **lst)
{
	t_basic_list			*tmp;

	tmp = NULL;
	while (lst && *lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_strdel(&(tmp->data));
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}
