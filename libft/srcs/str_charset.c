#include <stdlib.h>
#include "libft.h"

int					str_charset(char **str, char c, int start, int end)
{
	int					i;

	i = start;
	if (str == NULL || *str == NULL || start > end)
		return (0);
	while ((*str)[i] && i < end)
	{
		(*str)[i] = c;
		i++;
	}
	return (1);
}
