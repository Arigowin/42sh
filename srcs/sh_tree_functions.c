#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "libft.h"

t_node				*create_node(t_types type)
{
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- CREATE  NODE-----------------", 2);

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
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- CLEAR NODE -----------------", 2);
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
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- DEL TREE -----------------", 2);

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
