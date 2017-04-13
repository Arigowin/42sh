#include "shell.h"
#include "libft.h"

int					fill_leaf(t_e_list **l_expr, t_node **node)
{
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- FILL LEAF -----------------", 2);

	(*node)->quote = (*l_expr)->hrd_quote;
	if ((*l_expr)->data && ((*node)->data = ft_strdup((*l_expr)->data)) == NULL)
		return (ERROR);
	return (TRUE);
}

t_types				fill_red_type(char *data, int *nb_hrd)
{
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- FILL RED TYPE -----------------", 2);

	t_types				type;

	type = ft_strequ(data, ">") ? RRED : RED;
	type = ft_strequ(data, ">>") ? DRRED : type;
	type = ft_strequ(data, "<") ? LRED : type;
	type = ft_strequ(data, "<<") ? DLRED : type;
	type = ft_strequ(data, "<>") ? RWRED : type;
	*nb_hrd += (type == DLRED ? 1 : 0);
	return (type);
}

int					parser_ret_fct(int ret, t_node **tree, t_node **node,
					t_node **to_free)
{
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- PARSER RET FCT -----------------", 2);

	if (tree && node && *node)
		*tree = *node;
	if (node && *node)
	*node = NULL;
	del_tree(to_free);
	return (ret);
}

int					move_in_list(t_e_list **l_expr)
{
	if (DEBUG_LP == 0)
		ft_putendl_fd("---------------- MOVE IN LIST -----------------", 2);

	if ((*l_expr) && (*l_expr)->next)
	{
		(*l_expr) = (*l_expr)->next;
		return (TRUE);
	}
	return (FALSE);
}
