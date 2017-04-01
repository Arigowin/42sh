#include "libft.h"

void					ft_basiclstfree(t_basic_list **lst)
{
	t_basic_list			*tmp;

	tmp = NULL;
	while (lst && *lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_strdel(&(tmp->data));
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}
