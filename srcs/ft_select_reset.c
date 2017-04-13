/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/13 17:37:07 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include "ft_select.h"
#include "libft.h"

int				disable_keyboard(void)
{
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
	char	*str;

	if ((str = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

void			termcap_reset(void)
{
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
