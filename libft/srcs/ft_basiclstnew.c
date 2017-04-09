#include "libft.h"

t_basic_list			*ft_basiclstnew(char *data, int nb)
{
	t_basic_list			*new;

	if ((new = (t_basic_list *)malloc(sizeof(t_basic_list))) == NULL)
		return (NULL);
	new->data = NULL;
	new->next = NULL;
	if (data == NULL)
		return (NULL);
	new->data = ft_strdup(data);
	new->nb = nb;
	return (new);
}
