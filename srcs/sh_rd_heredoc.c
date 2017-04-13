/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rd_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:48:55 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:48:56 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#define RA RED_ARG

int					tree_trav_hrd(t_line *stline, t_node **tree,
					t_history **history)
{
	if (*tree && (*tree)->left)
	{
		if (heredoc_handler(stline, &((*tree)->left), history) == ERROR)
			return (ERROR);
	}
	if (*tree && (*tree)->right)
	{
		if (heredoc_handler(stline, &((*tree)->right), history) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

int					check_end_heredoc(t_line *stline)
{
	if (ft_strcmp(stline->hrd.deli->data, stline->hrd.ptr) == 0)
		return (BREAK);
	stline->hrd.ptr = &((stline->hrd.line)[stline->hrd.pos + 1]);
	return (CONTINUE);
}

char				*hrd_quote_dup(char *str, int len, int type)
{
	char				*ret;
	char				*tmp;

	ret = ft_strnew(ft_strlen(str));
	while (str && *str)
	{
		if (*str == '\\' && type == 8)
		{
			str++;
			ft_strncat(ret, str, 1);
		}
		else if (*str == '$' && type == 8)
			token_dollar(&str, &ret, TRUE);
		else
			ft_strncat(ret, str, 1);
		str++;
	}
	tmp = ft_strsub(ret, 0, ft_strlen(ret) - len);
	ft_strdel(&ret);
	return (tmp);
}

static int			fill_hrd_content(t_line *stline, t_node **tree)
{
	int					len;
	int					len_deli;

	len_deli = (stline->hrd.ctrl_d == FALSE ? ft_strlen(stline->hrd.deli->data)
											: 0);
	len = (ft_strlen(stline->hrd.line) - (len_deli + 1));
	if (tree && (*tree) && (*tree)->right && ((*tree)->right->type == HRD_QUOTE
	|| (*tree)->right->type == RED_ARG))
	{
		if ((*tree)->right->type == HRD_QUOTE)
		{
			if (((*tree)->right->right->data =
			ft_strsub(stline->hrd.line, 0, len + 1)) == NULL)
				return (sh_error(FALSE, 6, NULL, NULL));
		}
		else if (((*tree)->right->right->data = hrd_quote_dup(stline->hrd.line,
		len_deli, (*tree)->right->type)) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
	}
	else if (((*tree)->right->right->right->data =
	ft_strsub(stline->hrd.line, 0, len + 1)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	return (TRUE);
}

int					manage_hrd_document(int bln, t_line *stline, t_node **tree,
		t_history **history)
{
	stline->hrd.deli = (((*tree)->right->type == RA || (*tree)->right->type
						== HRD_QUOTE) ? (*tree)->right : (*tree)->right->right);
	stline->hrd.ptr = stline->hrd.line;
	if (bln)
		mini_prt_handler(&(stline->hrd.line), &(stline->hrd.pos), stline);
	else
		miniprt_reset_stline(stline);
	check_signal(4);
	if (fct_read(TRUE, stline, history) == ERROR)
		return (ERROR);
	check_signal(3);
	if (stline->hrd.ctrl_d == FALSE)
		ft_putendl("");
	if ((stline->hrd.line)[0] == '\0')
		return (ERROR);
	if ((stline->hrd.deli->right = create_node(DLRED_DOC)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	if (fill_hrd_content(stline, tree) == ERROR)
		return (ERROR);
	if (stline->hrd.line)
		ft_bzero(stline->hrd.line, ft_strlen(stline->hrd.line));
	stline->hrd.pos = 0;
	stline->hrd.ctrl_d = FALSE;
	(stline->hrd.nb)--;
	return (TRUE);
}
