#include "shell.h"
#include "libft.h"
#include "ft_select.h"

static char			*expander(char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- EXPANDER ----------");

	char				*buff;

	if (word == NULL)
		return (FALSE);
	if ((buff = ft_strnew(ft_strlen(word))) == NULL)
	{
		sh_error(FALSE, 6, NULL, NULL);
		return (NULL);
	}
	while (word && *word)
	{
		if (*word == '$')
		{
			token_dollar(&word, &buff, FALSE);
			if (!(*word))
				break ;
			word++;
		}
		if (!(*word))
			break ;
		add_in_tbl(&buff, *word);
		word++;
	}
	return (buff);
}

int					complet_var(t_basic_list **lst, char **path, char **word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPLET VAR ----------");

	char				*tmp;

	if (!(*word && ft_strchr(*word, '$')))
		return (FALSE);
	tmp = expander(*word);
	ft_strdel(word);
	if ((*word = ft_strdup(tmp)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	split_path(word, path);
	if (ft_strchr(*word, '$'))
	{
		get_varlist(lst, word);
		return (TRUE);
	}
	return (FALSE);
}

int				init_getdircontent(t_basic_list **lst, char **path,
		char **word, int file)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- INIT GETDIRCONTENT ----------");

	if (*path == NULL)
		split_path(word, path);
	parse_tilde(path);
	get_dircontent(file, *path, lst, *word);
	return (TRUE);
}
