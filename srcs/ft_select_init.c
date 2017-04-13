/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/13 17:36:59 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft_select.h"
#include "libft.h"
#include "shell.h"

int				enable_keyboard(void)
{
	char	*str;

	if ((str = tgetstr("ke", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				hide_cursor(void)
{
	char	*str;

	if ((str = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				termcap_init(void)
{
	char				*name_term;

	manage_signal();
	if ((get_stuff()->fd = open(ttyname(0), O_WRONLY | O_NOCTTY)) == -1)
		return (-1);
	if ((name_term = get_env("TERM", ENV, TRUE)) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	ft_strdel(&name_term);
	if (tcgetattr(get_stuff()->fd, get_term()) == -1)
		return (-1);
	get_term()->c_lflag &= ~(ICANON | ECHO);
	get_term()->c_cc[VMIN] = 1;
	get_term()->c_cc[VTIME] = 0;
	if (tcsetattr(get_stuff()->fd, TCSADRAIN, get_term()) == -1)
		return (-1);
	tputs(tgetstr("ti", NULL), 1, ft_putchr);
	hide_cursor();
	enable_keyboard();
	get_s_win();
	return (0);
}
