#include "libft.h"

int 				free_tduo_link(t_duo **lst)
{
	t_duo				*tmp;

	tmp = NULL;
	if (lst == NULL)
		return (-1);
	tmp = (*lst)->next;
	ft_strdel(&((*lst)->name));
	ft_strdel(&((*lst)->value));
	ft_strdel(&((*lst)->tmp_val));
	free(*lst);
	*lst = tmp;
	tmp = NULL;
	return (0);
}
