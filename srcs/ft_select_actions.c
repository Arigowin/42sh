/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:28 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:28 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "ft_select.h"

char				*enter_key(void)
{
	char				*ret;
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	ret = NULL;
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
			break ;
		tmp = tmp->next;
	}
	if ((ret = ft_strdup(tmp->next->name)) == NULL)
		return (NULL);
	return (ret);
}

char				*esc_key(void)
{
	termcap_reset();
	return (NULL);
}

int					col_number(t_cduo *node)
{
	int					nb;

	nb = node->no_elt / fct_size()->ws_row;
	nb++;
	return (nb);
}

void				right_arrow(void)
{
	t_cduo				*tmp;
	int					stop;
	int					i;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor != TRUE)
		tmp = tmp->next;
	stop = fct_size()->ws_row;
	if (col_number(tmp) + 1 == get_stuff()->nb_col
			&& tmp->no_elt + stop >= get_stuff()->nb_elt)
		stop += ((get_stuff()->nb_elt % fct_size()->ws_row) + 1);
	else if (col_number(tmp) + 0 == get_stuff()->nb_col)
		stop = (get_stuff()->nb_elt % fct_size()->ws_row) + 1;
	i = 0;
	while (i < stop)
	{
		down_arrow(0);
		i++;
	}
}

void				left_arrow(void)
{
	t_cduo				*tmp;
	int					stop;
	int					i;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor != TRUE)
		tmp = tmp->next;
	if (col_number(tmp) == 1)
	{
		while (tmp->next->first != TRUE)
		{
			up_arrow(0);
			tmp = tmp->prev;
		}
		return ;
	}
	stop = fct_size()->ws_row;
	i = 0;
	while (i < stop)
	{
		up_arrow(0);
		i++;
	}
}
