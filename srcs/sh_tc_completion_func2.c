#include "shell.h"
#include "libft.h"
#include "ft_select.h"

int					complet_var(t_basic_list **lst, char **word, char **path)
{
	char				*tmp;
	char				*tmp2;

	(void)lst;
	if (*path && ft_strchr(*path, '$'))
	{
		tmp = ft_strnew(ft_strlen(*path));
		while (*path && **path)
		{
			if (**path == '$')
			{
				token_dollar(path, &tmp);
				(*path)++;
			}
			add_in_tbl(&tmp, **path);
			(*path)++;
		}
		*path = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (*word && ft_strchr(*word, '$'))
	{
		tmp = ft_strnew(ft_strlen(*word));
		tmp2 = *word;
		while (tmp2 && *tmp2)
		{
			if (*tmp2 == '$')
			{
				token_dollar(&tmp2, &tmp);
				(tmp2)++;
			}
			add_in_tbl(&tmp, *tmp2);
			(tmp2)++;
		}
		printf("\nword[%s] tmp[%s] tmp2[%s]\n", *word, tmp, tmp2);
		if (ft_strlen(*word) < ft_strlen(tmp))
		{
			*word = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	printf("\npath [%s] word[%s]\n", *path, *word);
	return (TRUE);
}
