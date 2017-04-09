/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struct.c                                    :+:      :+:    :+:   */
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
#include <unistd.h>
#include <sys/ioctl.h>
#include "ft_select.h"
#include "libft.h"

t_glst			*get_stuff(void)
{
	static t_glst	*stuff = NULL;

	if (stuff == NULL)
	{
		stuff = (t_glst *)malloc(sizeof(t_glst));
		stuff->lst_param = NULL;
		stuff->fd = -1;
		stuff->max_len = 0;
		stuff->nb_elt = 0;
		stuff->nb_col = 0;
		stuff->col_size = 0;
	}
	return (stuff);
}

t_termios		*get_term(void)
{
	static t_termios	*term = NULL;

	if (term == NULL)
		term = (t_termios *)malloc(sizeof(t_termios));
	return (term);
}

t_winsize		*fct_size(void)
{
	static t_winsize	*win_size = NULL;

	if (win_size == NULL)
		win_size = (t_winsize *)malloc(sizeof(t_winsize));
	return (win_size);
}

int				get_s_win(void)
{
	ioctl(get_stuff()->fd, TIOCGWINSZ, fct_size());
	return (0);
}
