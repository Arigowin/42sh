/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tc_move_in_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:49:42 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:49:43 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "shell.h"
#include "libft.h"

static int			multi_left(char **str, int *pos, t_line *stline)
{
	int					nb;
	char				*tmp;
	char				*chr;

	tmp = NULL;
	if ((*str)[*pos - 1] == '\n')
	{
		if ((tmp = ft_strsub(*str, 0, ft_strlen(*str) -
		ft_strlen(&((*str)[*pos - 1])))) == NULL)
			return (ERROR);
		nb =
			(chr = ft_strrchr(tmp, '\n')) ? ft_strlen(chr + 1) : ft_strlen(tmp);
		if (stline->curs_y == 0)
			nb += PRT_LEN;
		if (nb > stline->win.ws_col)
			nb -= (stline->win.ws_col * (nb / stline->win.ws_col)) - PRT_LEN;
		while (++(stline->curs_x) < nb - 1)
			tputs(tgetstr("nd", NULL), 1, my_outc);
		stline->curs_x = nb + 1;
	}
	while ((*str)[*pos - 1] != '\n' && ++(stline->curs_x) < stline->win.ws_col)
		tputs(tgetstr("nd", NULL), 1, my_outc);
	return (dblstr_duo_ret(TRUE, &tmp, NULL, NULL));
}

int					fct_left(char **str, int *pos, t_line *stline,
					t_history **history)
{
	(void)history;
	if (*str && *pos > 0 && ((stline->curs_y == 0 && stline->curs_x > 2)
	|| stline->curs_y > 0))
	{
		if (stline->copy.start != -1 && (*pos) > stline->copy.start)
			del_in_copy(str, pos, stline, LEFT);
		(stline->curs_x)--;
		if (stline->curs_x < 0 && stline->curs_y > 0)
		{
			tputs(tgetstr("up", NULL), 1, my_outc);
			stline->curs_x = -1;
			(stline->curs_y)--;
			multi_left(str, pos, stline);
			(stline->curs_x)--;
			if (stline->curs_x > 0)
				tputs(tgetstr("nd", NULL), 1, my_outc);
		}
		else
			tputs(tgetstr("le", NULL), 1, my_outc);
		((*pos))--;
		if (stline->copy.start != -1 && (*pos) < stline->copy.start)
			add_in_copy(str, pos, stline, LEFT);
	}
	return (TRUE);
}

int					fct_right(char **str, int *pos, t_line *stline,
					t_history **history)
{
	(void)history;
	if ((stline->copy.start == -1 && ((*pos))
		< (int)ft_strlen(*str)) || (stline->copy.start != -1
		&& ((*pos)) < (int)ft_strlen(*str) - 1))
	{
		if (stline->copy.start != -1 && (*pos) < stline->copy.start)
			del_in_copy(str, pos, stline, RIGHT);
		if (stline->curs_x >= stline->win.ws_col - 1 || (*str)[*pos] == '\n')
		{
			(stline->curs_x) = 0;
			(stline->curs_y)++;
			tputs(tgetstr("cr", NULL), 1, my_outc);
			tputs(tgetstr("do", NULL), 1, my_outc);
		}
		else
		{
			(stline->curs_x)++;
			tputs(tgetstr("nd", NULL), 1, my_outc);
		}
		((*pos))++;
		if (stline->copy.start != -1 && (*pos) > stline->copy.start)
			add_in_copy(str, pos, stline, RIGHT);
	}
	return (TRUE);
}

int					fct_ctrl_left(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					x;

	if (*pos > 0 && ((stline->curs_y == 0 && stline->curs_x > 2)
	|| stline->curs_y > 0))
		fct_left(str, pos, stline, history);
	x = (*pos);
	while (x > 0 && ((stline->curs_y == 0 && stline->curs_x > 2)
	|| stline->curs_y > 0))
	{
		if (((*str)[x - 1] == ' ' || (*str)[x - 1] == '\n') && (*str)[x] != ' ')
			break ;
		fct_left(str, pos, stline, history);
		x = (*pos);
	}
	return (TRUE);
}

int					fct_ctrl_right(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					x;

	(void)history;
	if (((*pos)) < (int)ft_strlen(*str))
		fct_right(str, pos, stline, history);
	x = (*pos);
	while ((x) < (int)ft_strlen(*str))
	{
		if (((*str)[x - 1] == ' ' || (*str)[x - 1] == '\n') && (*str)[x] != ' ')
			break ;
		fct_right(str, pos, stline, history);
		x = (*pos);
	}
	return (TRUE);
}
