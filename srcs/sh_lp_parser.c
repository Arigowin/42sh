#include <stdlib.h>
#include "shell.h"
#include "libft.h"

static int			check_command(int *nb_hrd, t_e_list **l_expr, t_node **tree)
{
	t_node				*save;
	t_node				*node;
	int					ret;

	save = *tree;
	node = create_node(CMD);
	if ((ret = check_red(nb_hrd, l_expr, &(node->left))) != TRUE)
		*tree = save;
	if ((*l_expr)->type == CMD)
	{
		if (fill_leaf(l_expr, &node) == ERROR)
		{
			del_tree(&node);
			return (sh_error(FALSE, 6, NULL, NULL));
		}
		if ((ret = check_next(nb_hrd, l_expr, &node, &(node->right))) < 0)
			return (parser_ret_fct(ret, NULL, NULL, &node));
		return (parser_ret_fct(TRUE, tree, &node, NULL));
	}
	if (ret == TRUE && (*l_expr)->type != CMD)
		return (parser_ret_fct(TRUE, tree, &(node->left), &node));
	del_tree(&node);
	return (sh_error(ret, 26, (*l_expr)->data, NULL));
}

static int			check_c_pipe(int *nb_hrd, t_e_list **l_expr, t_node **tree)
{
	t_node				*node;
	t_node				**node_to_give;
	int					ret;

	node = create_node(PIPE);
	node_to_give = (node->left == NULL ? &(node->left) : &(node->right));
	if ((ret = check_command(nb_hrd, l_expr, node_to_give)) == TRUE
	&& (*l_expr)->type != AMP)
	{
		if ((*l_expr)->type == PIPE)
		{
			if (fill_leaf(l_expr, &node) == ERROR)
				return (error_clear_node(FALSE, 6, NULL, &node));
			*tree = node;
			if (!(move_in_list(l_expr) && (ret = check_c_pipe(nb_hrd, l_expr,
			&(node->right)))))
				return (error_clear_node(ret, 26, (*l_expr)->data, &node));
			return (ret);
		}
		return (parser_ret_fct(ret, tree, node_to_give, &node));
	}
	return (error_clear_node(ret, 26, (*l_expr)->data, &node));
}

static int			check_logic(int *nb_hrd, t_e_list **l_expr, t_node **tree)
{
	t_node				*node;
	t_node				**node_to_give;
	int					ret;

	node = create_node(SEMI);
	node_to_give = (node->left == NULL ? &(node->left) : &(node->right));
	if ((ret = check_c_pipe(nb_hrd, l_expr, node_to_give)) == TRUE)
	{
		if ((*l_expr)->type == LOGIC_OR || (*l_expr)->type == LOGIC_AND)
		{
			node->type = (*l_expr)->type;
			if (fill_leaf(l_expr, &node) == ERROR)
				return (error_clear_node(FALSE, 6, NULL, &node));
			*tree = node;
			if (!(move_in_list(l_expr)
			&& (ret = check_logic(nb_hrd, l_expr, &(node->right)))))
				return (error_clear_node(TRUE, 26, (*l_expr)->data, &node));
			return (ret);
		}
		return (parser_ret_fct(ret, tree, node_to_give, &node));
	}
	del_tree(&node);
	return (sh_error(ret, 26, (*l_expr)->data, NULL));
}

static int			check_expr(int *nb_hrd, t_e_list **l_expr, t_node **tree)
{
	t_node				*node;
	t_node				**node_to_give;
	int					ret;

	ret = 0;
	node = create_node(SEMI);
	node_to_give = (node->left == NULL ? &(node->left) : &(node->right));
	if ((*l_expr)->type == SEMI || ((*l_expr)->type != SEMI
	&& (ret = check_logic(nb_hrd, l_expr, node_to_give)) == TRUE))
	{
		if ((*l_expr)->type == SEMI)
		{
			if (fill_leaf(l_expr, &node) == ERROR)
				return (error_clear_node(FALSE, 6, NULL, &node));
			*tree = node;
			if ((ret = move_in_list(l_expr))
			&& ((ret = check_expr(nb_hrd, l_expr, &(node->right))) < 0))
				return (ret);
			return (TRUE);
		}
		return (parser_ret_fct(ret, tree, node_to_give, &node));
	}
	del_tree(&node);
	return (sh_error(ret, 26, (*l_expr)->data, NULL));
}

int					parser(int *nb_hrd, t_e_list **l_expr, t_node **tree)
{
	int					ret;

	if (*l_expr == NULL)
		return (FALSE);
	ret = check_expr(nb_hrd, l_expr, tree);
	return (ret);
}
