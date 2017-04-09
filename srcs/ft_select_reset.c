/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:29 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include "ft_select.h"
#include "libft.h"

int				disable_keyboard(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- DISABLE KEYBOARD ----------");

	char	*str;

	if (tgetstr("ks", NULL) == NULL)
		return (-1);
	if ((str = tgetstr("ki", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				display_cursor(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- DISPLAY CURSOR ----------");

	char	*str;

	if ((str = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

void			termcap_reset(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- TERMCAP RESET ----------");

	t_termios		*termios;
	t_winsize		*win_size;
	t_glst			*stuff;

	clr_screen();
	tputs(tgetstr("te", NULL), 1, ft_putchr);
	display_cursor();
	disable_keyboard();
	tcgetattr(get_stuff()->fd, get_term());
	get_term()->c_lflag |= (ICANON | ECHO);
	tcsetattr(get_stuff()->fd, 0, get_term());
	close(get_stuff()->fd);
	termios = get_term();
	free(termios);
	win_size = fct_size();
	free(win_size);
	free_lst_param();
	stuff = get_stuff();
	free(stuff);
}
