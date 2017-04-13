/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tree_traversal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:44:10 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:14:09 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int			tree_trav_semi(t_node *tree, t_lst_fd **lstfd,
					int pipefd_tab[2][2])
{
	int					fct_ret;

	fct_ret = -1;
	if (tree && tree->left)
		if ((tree_traversal(tree->left, lstfd, pipefd_tab)) == ERROR)
			return (ERROR);
	init_pipefd(pipefd_tab);
	fct_ret = savior_fct_ret(0, FALSE);
	if (tree && tree->right
	&& (tree->type == SEMI
	|| (tree->type == LOGIC_AND && fct_ret == 0)
	|| (tree->type == LOGIC_OR && fct_ret != 0)))
		if ((tree_traversal(tree->right, lstfd, pipefd_tab)) == ERROR)
			return (ERROR);
	return (TRUE);
}

static int			tree_trav_pipe(t_node *tree, t_lst_fd **lstfd,
					int pipefd_tab[2][2])
{
	int					ret;

	ret = TRUE;
	if ((ret = (pipe_function(pipefd_tab, tree, lstfd))) != TRUE)
		return (ret);
	if ((ret = (tree_traversal(tree->right, lstfd, pipefd_tab))) != TRUE)
		return (ret);
	if (pipefd_tab[0][0] != -2)
		close(pipefd_tab[0][0]);
	if (pipefd_tab[0][1] != -2)
		close(pipefd_tab[0][1]);
	if (pipefd_tab[1][0] != -2)
		close(pipefd_tab[1][0]);
	if (pipefd_tab[1][1] != -2)
		close(pipefd_tab[1][1]);
	reset_std_fd();
	close_lstfd(lstfd);
	del_lstfd(lstfd);
	return (ret);
}

static int			tree_trav_cmd(t_node *tree, t_lst_fd **lstfd)
{
	t_lst_fd			*tmpfd;

	tmpfd = NULL;
	if (tree->left != NULL && (*lstfd))
	{
		tree = tree->left;
		while (tree)
		{
			if (tree->type != DLRED)
			{
				tmpfd = (*lstfd)->next;
				if ((*lstfd)->fd > 2)
					close((*lstfd)->fd);
				ft_strdel(&((*lstfd)->filename));
				free(*lstfd);
				*lstfd = tmpfd;
			}
			tree = tree->left;
		}
	}
	return (TRUE);
}

int					tree_traversal(t_node *tree, t_lst_fd **lstfd,
					int pipefd_tab[2][2])
{
	int					ret;

	ret = 0;
	savior_tty(ttyname(1), TRUE);
	if (tree &&
	(tree->type == SEMI || tree->type == LOGIC_OR || tree->type == LOGIC_AND))
		if (tree_trav_semi(tree, lstfd, pipefd_tab) == ERROR)
			return (ERROR);
	if (tree && tree->type != SEMI && tree->type != LOGIC_OR
	&& tree->type != LOGIC_AND && lstfd && *lstfd == NULL)
		red_fd(-2, tree, lstfd, NONE);
	if (tree->type == PIPE && (ret == tree_trav_pipe(tree, lstfd, pipefd_tab)))
		return (ret);
	if (tree->type == CMD)
	{
		if ((manage_cmd(pipefd_tab, tree, lstfd)) == ERROR)
			return (ERROR);
		tree_trav_cmd(tree, lstfd);
		if (pipefd_tab[0][0] < 0 && pipefd_tab[1][0] < 0)
		{
			reset_std_fd();
			del_lstfd(lstfd);
		}
	}
	return (TRUE);
}
