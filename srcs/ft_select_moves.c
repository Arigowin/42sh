/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/08 10:34:33 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

static int		dw_first(t_cduo *tmp, int pos, int displayed_col)
{
	if (tmp->next->no_elt >= (fct_size()->ws_row * displayed_col + pos)
			&& tmp->next->first == FALSE)
	{
		tmp = get_stuff()->lst_param;
		while (tmp->first_disp != TRUE)
			tmp = tmp->next;
		tmp->first_disp = FALSE;
		while (tmp->no_elt < (pos + fct_size()->ws_row))
			tmp = tmp->next;
		tmp->first_disp = TRUE;
	}
	else if (tmp->next->first == TRUE)
	{
		tmp = get_stuff()->lst_param;
		while (tmp->first_disp != TRUE)
			tmp = tmp->next;
		tmp->first_disp = FALSE;
		tmp = get_stuff()->lst_param;
		tmp->first_disp = TRUE;
	}
	return (0);
}

int				down_arrow(int space)
{
	t_cduo				*tmp;
	int					pos;
	int					displayed_col;

	pos = 0;
	displayed_col = fct_size()->ws_col / get_stuff()->col_size;
	tmp = get_stuff()->lst_param;
	while (tmp->first_disp != TRUE)
		tmp = tmp->next;
	pos = tmp->no_elt;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor != TRUE)
		tmp = tmp->next;
	(void)space;
	tmp->prev->select = FALSE;
	tmp->select = TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	dw_first(tmp, pos, displayed_col);
	return (0);
}

static int		up_first(t_cduo *tmp, int displayed_col)
{
	int					pos;
	int					next_pos;

	pos = 0;
	next_pos = 0;
	if (tmp->first == FALSE && tmp->first_disp == TRUE
			&& displayed_col < get_stuff()->nb_col)
	{
		pos = tmp->no_elt;
		tmp->first_disp = FALSE;
		next_pos = pos - fct_size()->ws_row < 1 ? 1 : pos - fct_size()->ws_row;
		while (tmp->no_elt != next_pos)
			tmp = tmp->prev;
		tmp->first_disp = TRUE;
	}
	else if (tmp->first == TRUE && tmp->first_disp == TRUE
			&& displayed_col < get_stuff()->nb_col)
	{
		tmp->first_disp = FALSE;
		while (tmp->no_elt != (((get_stuff()->nb_col - displayed_col)
						* fct_size()->ws_row) + 1))
			tmp = tmp->prev;
		tmp->first_disp = TRUE;
	}
	return (0);
}

int				up_arrow(void)
{
	t_cduo				*tmp;
	int					displayed_col;

	displayed_col = fct_size()->ws_col / get_stuff()->col_size;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->prev;
	tmp->cursor = FALSE;
	tmp->prev->cursor = TRUE;
	up_first(tmp, displayed_col);
	return (0);
}
