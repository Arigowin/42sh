#include "libft.h"

int 				free_tduo_link(t_duo **lst)
{
	t_duo				*tmp;

	tmp = NULL;
	if (lst == NULL)
		return (-1);
	tmp = *lst;
	ft_strdel(&(tmp->name));
	ft_strdel(&(tmp->value));
	*lst = tmp->next;
	free(tmp);
	tmp = NULL;
	return (0);
}
