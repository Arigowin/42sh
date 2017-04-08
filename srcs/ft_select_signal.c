/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/08 10:33:59 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>
#include "ft_select.h"
#include "libft.h"

static void		sig_winsize(int sig)
{
	t_cduo			*tmp;
	int				i;

	i = 0;
	(void)sig;
	get_s_win();
	clr_screen();
	get_col_size();
	get_stuff()->nb_col = get_stuff()->nb_elt / fct_size()->ws_row;
	tmp = get_stuff()->lst_param;
	while ((i += tmp->first) <= 2)
	{
		if (tmp->first_disp == TRUE)
			tmp->first_disp = FALSE;
		if (tmp->cursor == TRUE)
			tmp->cursor = FALSE;
		tmp = tmp->next;
	}
	tmp = get_stuff()->lst_param;
	tmp->first_disp = TRUE;
	tmp->cursor = TRUE;
	manage_columns();
}

static void		sig_interrupt(int sig)
{
	char			cp[2];

	(void)sig;
	cp[0] = get_term()->c_cc[VSUSP];
	cp[1] = 0;
	clr_screen();
	tputs(tgetstr("te", NULL), 1, ft_putchr);
	display_cursor();
	disable_keyboard();
	tcgetattr(get_stuff()->fd, get_term());
	get_term()->c_lflag |= (ICANON | ECHO);
	tcsetattr(get_stuff()->fd, 0, get_term());
	close(get_stuff()->fd);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, sig_continue);
	ioctl(0, TIOCSTI, cp);
}

void			sig_continue(int sig)
{
	(void)sig;
	get_stuff()->fd = open(ttyname(0), O_WRONLY);
	get_term()->c_lflag &= ~(ICANON | ECHO);
	get_term()->c_cc[VMIN] = 1;
	get_term()->c_cc[VTIME] = 0;
	tcsetattr(get_stuff()->fd, TCSADRAIN, get_term());
	hide_cursor();
	enable_keyboard();
	tputs(tgetstr("ti", NULL), 1, ft_putchr);
	clr_screen();
	get_s_win();
	manage_columns();
	signal(SIGTSTP, sig_interrupt);
}

static void		sig_exit_pgm(int sig)
{
	(void)sig;
	termcap_reset();
	exit(EXIT_FAILURE);
}

void			manage_signal(void)
{
	signal(SIGWINCH, sig_winsize);
	signal(SIGTSTP, sig_interrupt);
	signal(SIGCONT, sig_continue);
	signal(SIGINT, sig_exit_pgm);
	signal(SIGQUIT, sig_exit_pgm);
	signal(SIGTERM, sig_exit_pgm);
}
