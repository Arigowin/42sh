/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tree_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:50:10 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:50:10 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "libft.h"

t_node				*create_node(t_types type)
{
	t_node				*new_node;

	if ((new_node = (t_node *)malloc(sizeof(t_node))) == NULL)
		sh_error(FALSE, 6, NULL, NULL);
	new_node->data = NULL;
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int					clear_node(t_node **node)
{
	if (node && *node)
	{
		ft_strdel(&((*node)->data));
		(*node)->left = NULL;
		(*node)->right = NULL;
		if (node && *node)
			free(*node);
		*node = NULL;
		return (TRUE);
	}
	return (FALSE);
}

int					del_tree(t_node **tree)
{
	if (tree && *tree)
	{
		if (tree && (*tree) && (*tree)->left)
			del_tree(&((*tree)->left));
		if (tree && (*tree) && (*tree)->right)
			del_tree(&((*tree)->right));
		if (tree)
			clear_node(tree);
		tree = NULL;
	}
	savior_tree(NULL, TRUE);
	return (TRUE);
}
