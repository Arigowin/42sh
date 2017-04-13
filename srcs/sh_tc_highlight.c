/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tc_highlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:49:24 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:49:25 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "shell.h"
#include "libft.h"

static int			init_highlight(char **str, t_line *stline)
{
	if (stline->copy.cpy != NULL)
	{
		if ((stline->copy.bkup = ft_strdup(stline->copy.cpy)) == NULL)
			sh_error(FALSE, 6, NULL, NULL);
		ft_strdel(&(stline->copy.cpy));
	}
	if ((stline->copy.cpy = ft_strnew(ft_strlen(*str))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	tputs(tgetstr("vi", NULL), 1, my_outc);
	return (TRUE);
}

static int			highlight(char **str, int *pos, t_line *stline,
					t_history **history)
{
	tputs(tgetstr("mr", NULL), 1, my_outc);
	ft_putchar_color(COLOR, (*str)[(*pos)]);
	stline->copy.pos = 0;
	stline->copy.cpy[stline->copy.pos] = (*str)[(*pos)];
	(*pos)++;
	stline->curs_x++;
	fct_left(str, pos, stline, history);
	stline->copy.pos++;
	stline->copy.start = (*pos);
	tputs(tgetstr("me", NULL), 1, my_outc);
	return (TRUE);
}

int					hide_highlight(char **str, int *pos, t_line *stline,
					t_history **history)
{
	char				*tmp;
	int					i;
	int					curs_pos;

	curs_pos = (*pos);
	if ((tmp = ft_strdup(*str)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	fct_end(str, pos, stline, history);
	while (((*pos)) > 0)
		fct_backspace(str, pos, stline, history);
	i = 0;
	while (tmp[i])
	{
		fct_insert(str, pos, tmp[i], stline);
		i++;
	}
	while ((*pos) != curs_pos)
	{
		if ((*pos) > curs_pos)
			fct_left(str, pos, stline, history);
		else if ((*pos) < curs_pos)
			fct_right(str, pos, stline, history);
	}
	tputs(tgetstr("ve", NULL), 1, my_outc);
	return (str_dbltbl_ret(TRUE, &tmp, NULL, NULL));
}

int					fct_highlight(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					len;

	len = ft_strlen(*str);
	if (stline->copy.start == -1)
	{
		init_highlight(str, stline);
		if ((*pos) == len)
			fct_left(str, pos, stline, history);
		highlight(str, pos, stline, history);
	}
	else
	{
		tputs(tgetstr("me", NULL), 1, my_outc);
		ft_strdel(&(stline->copy.cpy));
		if (stline->copy.bkup != NULL)
		{
			if ((stline->copy.cpy = ft_strdup(stline->copy.bkup)) == NULL)
				return (sh_error(FALSE, 6, NULL, NULL));
		}
		stline->copy.start = -1;
		hide_highlight(str, pos, stline, history);
		return (TRUE);
	}
	return (FALSE);
}
