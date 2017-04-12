/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/12 16:54:38 by dolewski         ###   ########.fr       */
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

	stuff = get_stuff();
	termios = get_term();
	win_size = fct_size();
	clr_screen();
	tputs(tgetstr("te", NULL), 1, ft_putchr);
	display_cursor();
	disable_keyboard();
	tcgetattr(stuff->fd, termios);
	termios->c_lflag |= (ICANON | ECHO);
	tcsetattr(stuff->fd, 0, termios);
	close(stuff->fd);
	free(termios);
	free(win_size);
	free_lst_param();
	free(stuff);
}
