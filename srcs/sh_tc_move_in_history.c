/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tc_move_in_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:49:33 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:49:34 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int			history_up_prev(t_history **history, char *tmp, int *pos,
					t_line *stline)
{
	char				*tmpchr;
	int					ret;
	int					len;

	if ((*history)->prev && tmp && *pos > 0)
	{
		len = ft_strlen((*history)->line);
		tmpchr = (stline->curs_y > 0 ? ft_strsub(tmp, ft_strlen(tmp) - len, len)
				: ft_strdup(ft_strrchr(tmp, '\n')));
		if (tmpchr != NULL && ft_strlen(tmpchr) > 1)
		{
			if (stline->curs_y == 0 && dup_move_one(&tmpchr) == ERROR)
				return (sh_error(FALSE, 6, NULL, NULL));
			ret = 0;
			if (ft_strcmp(tmpchr, (*history)->line) == 0)
				*history = (*history)->prev;
			*history = (*history)->prev;
		}
		else if ((ret = ft_strcmp(tmp, (*history)->line)) == 0)
			*history = (*history)->prev;
		ft_strdel(&tmpchr);
	}
	return (TRUE);
}

static int			nb_line_total(char *str, t_line *stline)
{
	char				**line;
	int					i;
	int					len;
	int					nb;

	nb = ft_strncount(str, '\n');
	line = ft_strsplit(str, '\n');
	i = 0;
	while (line && line[i])
	{
		len = ft_strlen(line[i]);
		if (len > stline->win.ws_col)
		{
			nb += (len) / stline->win.ws_col;
			nb -= (len % stline->win.ws_col == 0 ? 1 : 0);
		}
		i++;
	}
	free_tab(&line);
	return (nb);
}

static int			reset_pos_x_y(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					nb;
	int					len;
	int					nb_line;
	char				*tmp;

	tmp = NULL;
	nb = nb_line_total(*str, stline);
	if (nb > 0)
		stline->curs_y = nb;
	if (stline->curs_y > 0 && *str != NULL && *pos > 0)
	{
		tmp = ft_strrchr(*str, '\n');
		len = (tmp != NULL ? ft_strlen(tmp) - 1 : ft_strlen(*str));
		if (len > stline->win.ws_col)
		{
			len += PRT_LEN;
			nb_line = (len) / stline->win.ws_col;
			len = (len - (stline->win.ws_col * nb_line));
		}
		stline->curs_x = len;
	}
	savior_history(history, TRUE);
	return (TRUE);
}

int					history_up(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					i;
	char				*t;
	char				*tmpchr;

	if ((history = savior_history(NULL, FALSE)) == NULL || *history == NULL)
		return (FALSE);
	fct_end(str, pos, stline, history);
	t = (*pos > 0 && (*str)[*pos - 1] == '\n' ? ft_strsub(*str, 0, *pos - 1)
			: ft_strdup(*str));
	if ((*history)->next == NULL && *pos > 0 && ft_strcmp(t, (*history)->line))
	{
		if ((tmpchr = ft_strrchr(t, '\n')) && ft_strlen(tmpchr) > 1)
			stline->curr_hist = ft_strdup(tmpchr + 1);
		else if (*str && *pos > 0 && (*str)[*pos - 1] != '\n')
			stline->curr_hist = ft_strdup(*str);
	}
	history_up_prev(history, t, pos, stline);
	while (*pos > 0 && ((stline->curs_y == 0 && stline->curs_x > 2)
	|| stline->curs_y > 0))
		fct_backspace(str, pos, stline, history);
	i = -1;
	while (((*history)->line)[++i])
		fct_insert(str, pos, ((*history)->line)[i], stline);
	reset_pos_x_y(&((*history)->line), pos, stline, history);
	return (dblstr_duo_ret(TRUE, &t, NULL, NULL));
}

int					history_down(char **str, int *pos, t_line *stline,
					t_history **history)
{
	int					i;

	if ((history = savior_history(NULL, FALSE)) == NULL || *history == NULL
	|| (stline && stline->line && stline->curr_hist
	&& ft_strcmp(stline->curr_hist, stline->line) == 0))
		return (FALSE);
	i = -2;
	if ((*history)->next)
	{
		*history = (*history)->next;
		i = -1;
	}
	fct_end(str, pos, stline, history);
	while (*pos > 0 && ((stline->curs_y == 0 && stline->curs_x > 2)
	|| stline->curs_y > 0))
		fct_backspace(str, pos, stline, history);
	while (++i >= 0 && ((*history)->line)[i])
		fct_insert(str, pos, ((*history)->line)[i], stline);
	if (i == -1 && stline->curr_hist)
		while ((stline->curr_hist)[++i])
			fct_insert(str, pos, (stline->curr_hist)[i], stline);
	reset_pos_x_y(&((*history)->line), pos, stline, history);
	return (TRUE);
}
