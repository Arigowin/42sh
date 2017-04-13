/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tc_copy_paste.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:49:18 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:49:19 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "shell.h"
#include "libft.h"

int					fct_copy(char **str, int *pos, t_line *stline,
					t_history **history)
{
	if (stline->copy.start == -1)
		return (FALSE);
	tputs(tgetstr("me", NULL), 1, my_outc);
	stline->copy.start = -1;
	hide_highlight(str, pos, stline, history);
	return (TRUE);
}

int					fct_paste(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					i;

	i = 0;
	(void)history;
	if (!stline->copy.cpy || stline->copy.start != -1)
		return (FALSE);
	while (stline->copy.cpy[i])
	{
		fct_insert(str, pos, stline->copy.cpy[i], stline);
		i++;
	}
	tputs(tgetstr("me", NULL), 1, my_outc);
	return (TRUE);
}

int					fct_cut(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					curs_start;
	int					curs_end;

	curs_start = stline->copy.start;
	curs_end = (*pos);
	if (stline->copy.start == -1)
		return (FALSE);
	tputs(tgetstr("me", NULL), 1, my_outc);
	stline->copy.start = -1;
	if (curs_end > curs_start)
	{
		fct_del(str, pos, stline, history);
		while (--curs_end >= curs_start)
			fct_backspace(str, pos, stline, history);
	}
	else
	{
		while (curs_end < curs_start--)
			fct_right(str, pos, stline, history);
		fct_del(str, pos, stline, history);
		while ((*pos) > curs_end)
			fct_backspace(str, pos, stline, history);
	}
	tputs(tgetstr("ve", NULL), 1, my_outc);
	return (TRUE);
}
