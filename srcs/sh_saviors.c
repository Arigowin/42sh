/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_saviors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:48:59 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:12:31 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

char				*savior_tty(char *tty, int code)
{
	static char			*save_tty = NULL;

	if ((save_tty == NULL && tty) || code == TRUE)
		save_tty = tty;
	return (save_tty);
}

t_line				*savior_stline(t_line *stline, int code)
{
	static t_line		*save = NULL;

	if ((save == NULL && stline) || code == TRUE)
		save = stline;
	return (save);
}

t_node				*savior_tree(t_node *tree, int code)
{
	static t_node		*save = NULL;

	if (save == NULL || code == TRUE)
		save = tree;
	return (save);
}

t_history			**savior_history(t_history **history, int code)
{
	static t_history		*save = NULL;

	if (history && *history && (save == NULL || code == TRUE))
		save = *history;
	return (&save);
}

int					savior_fct_ret(int ret, int code)
{
	static int		save = -1;

	if (save == -1 || code == TRUE)
		save = ret;
	return (save);
}
