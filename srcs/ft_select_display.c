/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:28 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:28 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_select.h"
#include "libft.h"
#include "shell.h"

int				get_col_size(void)
{
	int				col_width;

	get_stuff()->nb_col = get_stuff()->nb_elt / fct_size()->ws_row;
	if (get_stuff()->nb_elt % fct_size()->ws_row != 0)
		get_stuff()->nb_col++;
	col_width = fct_size()->ws_col / get_stuff()->nb_col;
	if (col_width > 20 && col_width > get_stuff()->max_len)
		col_width = get_stuff()->max_len;
	else if (col_width < 20 && get_stuff()->max_len > 20)
		col_width = 20;
	else if (col_width < 20 && get_stuff()->max_len < 20)
		col_width = get_stuff()->max_len;
	get_stuff()->col_size = col_width + 2;
	return (0);
}

int				manage_win_size(void)
{
	int				nb_min_row;
	int				nb_min_col;
	int				win_min_widht;

	nb_min_row = get_stuff()->nb_elt > 20 ? 20 : get_stuff()->nb_elt;
	win_min_widht = get_stuff()->max_len * get_stuff()->nb_col;
	nb_min_col = win_min_widht > 100 ? 100 : win_min_widht;
	if (fct_size()->ws_row < nb_min_row && fct_size()->ws_col < nb_min_col)
	{
		clr_screen();
		tputs(tgoto(tgetstr("cm", NULL), (fct_size()->ws_col - 18) / 2,
				nb_min_row / 2), 1, ft_putchr);
		tputs("WINDOW TOO SMALL !!", 1, ft_putchr);
	}
	return (0);
}

int				print_return(char ***ret)
{
	int					i;

	i = 0;
	while ((*ret)[i] != NULL)
	{
		ft_putstr_fd((*ret)[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	free_tab(ret);
	return (0);
}
