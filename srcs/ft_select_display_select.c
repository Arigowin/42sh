/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_select.c                                   :+:      :+:    :+:   */
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

static int		putchr_max_len_fd(char *str, int col_size)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- PUTCHAR MAX LEN FD ----------");

	int				i;

	i = 0;
	if (col_size == 0)
		col_size = get_stuff()->nb_elt > fct_size()->ws_row ?
			get_stuff()->col_size - 4 : fct_size()->ws_col - 4;
	while (i < (col_size))
	{
		ft_putchar_fd(str[i], get_stuff()->fd);
		i++;
	}
	ft_putstr_fd("...", get_stuff()->fd);
	return (0);
}

static int		three_dots_up(int len, t_cduo *tmp)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- THREE DOTS UP ----------");

	int				i;

	i = len > (get_stuff()->col_size - 6) ? (get_stuff()->col_size - 10) : len;
	if (len >= (get_stuff()->col_size - 1))
	{
		i = get_stuff()->col_size - 10;
		putchr_max_len_fd(tmp->name, i);
	}
	else
		tputs(tmp->name, 1, ft_putchr);
	ft_putstr_fd("\033[0m", get_stuff()->fd);
	tputs(tgoto(tgetstr("cm", NULL), get_stuff()->col_size - 6,
		0), 1, ft_putchr);
	tputs("[...]", 1, ft_putchr);
	return (0);
}

static int		three_dots_down(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- THREE DOTS DOWN ----------");

	tputs(tgoto(tgetstr("cm", NULL), fct_size()->ws_col - 5,
		fct_size()->ws_row), 1, ft_putchr);
	tputs("[...]", 1, ft_putchr);
	return (0);
}

static int		manage_display(int j, int k, t_cduo *tmp)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- MANAGE DISPLAY ----------");

	int				len;

	tputs(tgoto(tgetstr("cm", NULL),
		(k * (get_stuff()->col_size)), j), 1, ft_putchr);
	len = ft_strlen(tmp->name);
	if (fct_size()->ws_col - ((k * (get_stuff()->col_size))
				+ get_stuff()->col_size) >= 0)
	{
		if (tmp->select == TRUE)
			ft_putstr_fd("\033[7m", get_stuff()->fd);
		if (tmp->cursor == TRUE)
			ft_putstr_fd("\033[4m", get_stuff()->fd);
		if ((get_stuff()->nb_elt <= fct_size()->ws_row
			&& len > fct_size()->ws_col) || (len > get_stuff()->col_size
			&& get_stuff()->nb_elt > fct_size()->ws_row))
			putchr_max_len_fd(tmp->name, 0);
		else if (tmp->first == FALSE && tmp->first_disp == TRUE)
			three_dots_up(len, tmp);
		else
			tputs(tmp->name, 1, ft_putchr);
		ft_putstr_fd("\033[0m", get_stuff()->fd);
	}
	else
		three_dots_down();
	return (0);
}

int				manage_columns(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- MANAGE COLUMNS ----------");

	t_cduo			*tmp;
	int				i[3];

	get_col_size();
	i[0] = 0;
	i[2] = -1;
	tmp = get_stuff()->lst_param;
	while (tmp->first_disp != TRUE)
		tmp = tmp->next;
	if (tmp->first == FALSE)
		(i[0])++;
	while ((i[0] += tmp->first) < 2)
	{
		tmp->col_nb = ++i[2];
		i[1] = -1;
		while (++i[1] < fct_size()->ws_row)
		{
			manage_win_size();
			manage_display(i[1], i[2], tmp);
			tmp = tmp->next;
			if (tmp->first == TRUE)
				break ;
		}
	}
	return (0);
}
