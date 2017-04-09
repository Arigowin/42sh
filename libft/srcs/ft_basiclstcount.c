#include "libft.h"

int					ft_basiclstcount(t_basic_list *lst)
{
	int					i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
