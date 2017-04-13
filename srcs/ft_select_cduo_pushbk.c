/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cduo_pushbk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:28 by avacher           #+#    #+#             */
/*   Updated: 2017/04/13 17:36:44 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

static t_cduo		*cduo_new(char *name)
{
	t_cduo			*new;

	if ((new = (t_cduo *)malloc(sizeof(t_cduo))) == NULL || name == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->first = FALSE;
	new->first_disp = FALSE;
	new->select = FALSE;
	new->cursor = FALSE;
	return (new);
}

int					cduo_pushback(t_cduo **lst, char *name, int no_elt)
{
	t_cduo			*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = cduo_new(name);
		(*lst)->first = TRUE;
		(*lst)->cursor = TRUE;
		(*lst)->first_disp = TRUE;
		(*lst)->no_elt = no_elt;
		(*lst)->next = *lst;
		(*lst)->prev = *lst;
		return (0);
	}
	while (tmp->next->first != TRUE)
		tmp = tmp->next;
	tmp->next = cduo_new(name);
	tmp->next->prev = tmp;
	tmp->next->next = *lst;
	tmp->next->no_elt = no_elt;
	(*lst)->prev = tmp->next;
	return (0);
}
