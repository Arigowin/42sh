/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:56 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:40:48 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "shell.h"
#include "libft.h"

static int			end_history(char **str, int *pos, t_line *stline,
					t_history **history)
{
	fct_end(str, pos, stline, history);
	while (history && *history && (*history)->next)
		*history = (*history)->next;
	savior_history(history, TRUE);
	return (TRUE);
}

static int			fct_return(char **str, int *pos, t_line *stline,
					t_history **history)
{
	end_history(str, pos, stline, history);
	stline->quote = quote_is_close(str);
	if (stline->quote != 0 || ((*pos == 1 && (*str)[*pos - 1]
	&& (*str)[*pos - 1] == '\\') || (*pos > 1 && (*str)[*pos - 1] &&
	(*str)[*pos - 2] && (*str)[*pos - 1] == '\\' && (*str)[*pos - 2] != '\\'))
	|| stline->hrd.nb > 0 || (*pos > 0 && check_end_pipe(str, pos)))
	{
		if (stline->hrd.nb > 0 && (check_end_heredoc(stline) == BREAK))
			return (BREAK);
		ft_strdel(&(stline->curr_hist));
		if (*str && (*str)[0] && stline->quote != 0)
			modif_history(history, *str, stline->mini_prt);
		return (mini_prt_handler(str, pos, stline));
	}
	else
	{
		(*str)[*pos] = '\0';
		if (stline->copy.cpy != NULL && stline->copy.start != -1)
			fct_highlight(str, pos, stline, history);
		if (*str && (*str)[0])
			modif_history(history, *str, stline->mini_prt);
		ft_putchar('\n');
		return (BREAK);
	}
	return (FALSE);
}

static t_key_fct	*tbl_key_fill(void)
{
	static t_key_fct	tbl_keys[19] =
	{{RETURN, fct_return}, {BACKSPACE, fct_backspace}, {DOWN, history_down},
		{HOME, fct_home}, {DEL, fct_del}, {CTRL_D, fct_ctrl_d}, {END, fct_end},
		{LEFT, fct_left}, {RIGHT, fct_right}, {UP, history_up},
		{CTRL_LEFT, fct_ctrl_left}, {CTRL_RIGHT, fct_ctrl_right},
		{CTRL_UP, fct_up}, {CTRL_DOWN, fct_down}, {CUT, fct_cut},
		{HIGHLIGHT, fct_highlight}, {PASTE, fct_paste}, {COPY, fct_copy},
		{TAB, fct_tab}};

	return (tbl_keys);
}

static int			insert_key(int key_to_insrt, t_line *stline)
{
	if (key_to_insrt > 31 && key_to_insrt < 128)
	{
		if (stline->hrd.nb <= 0)
			handle_quote(key_to_insrt, &(stline->line), &(stline->pos), stline);
		fct_insert((stline->hrd.nb > 0 ? &(stline->hrd.line) :
			&(stline->line)), (stline->hrd.nb > 0 ? &(stline->hrd.pos) :
				&(stline->pos)), key_to_insrt, stline);
	}
	return (TRUE);
}

int					event(int key_to_insrt, t_line *stline, t_history **history)
{
	int					i;
	int					ret;
	t_key_fct			*tbl_keys;

	tbl_keys = tbl_key_fill();
	i = -1;
	ret = 0;
	tputs(tgetstr("vi", NULL), 1, my_outc);
	while (++i < 19)
	{
		if (tbl_keys[i].key == key_to_insrt)
		{
			ret = (tbl_keys[i].fct((stline->hrd.nb > 0 ? &(stline->hrd.line)
					: &(stline->line)), (stline->hrd.nb > 0 ? &(stline->hrd.pos)
					: &(stline->pos)), stline, history));
			tputs(tgetstr("ve", NULL), 1, my_outc);
			return (ret);
		}
	}
	insert_key(key_to_insrt, stline);
	tputs(tgetstr("ve", NULL), 1, my_outc);
	return (TRUE);
}
