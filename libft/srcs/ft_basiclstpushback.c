#include "libft.h"

void				ft_basiclstpushbck(t_basic_list **alst, char *data, int nb)
{
	t_basic_list		*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (tmp == NULL)
	{
		*alst = ft_basiclstnew(data, nb);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_basiclstnew(data, nb);
}
