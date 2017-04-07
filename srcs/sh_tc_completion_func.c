#include "shell.h"
#include "libft.h"

static int			parse_tilde(char **path)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- PARSE TILDE ----------");

	char				*home;
	char				*tmp;

	tmp = NULL;
	home = NULL;
	if ((*path)[0] == '~' && (home = get_env("HOME")) != NULL)
	{
		tmp = ft_strdup(srch_value(*path, '~'));
		ft_strdel(path);
		*path = ft_strjoin(home, tmp);
		ft_strdel(&home);
		ft_strdel(&tmp);
	}
	return (TRUE);
}

static void			add_slash_after_path(char **word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- ADD SLASH AFTER PATH ----------");

	char				*tmp;

	tmp = NULL;
	if (ft_strlen(*word) == 1 && (*word)[0] == '~')
	{
		tmp = ft_strjoin(*word, "/");
		ft_strdel(word);
		*word = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

int					split_path(char **word, char **path)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("--------- SPLIT PATH ----------");

	char				*tmp;
	int					i;

	if ((i = ft_strlen(*word)) == 0)
		return (FALSE);
	while (i > -1 && (*word)[i] != '/')
		i--;
	*path = ft_strsub(*word, 0, i + 1);
	tmp = ft_strsub(*word, i + 1, ft_strlen(*word) - i);
	ft_strdel(word);
	*word = ft_strdup(tmp);
	ft_strdel(&tmp);
	parse_tilde(path);
	return (TRUE);
}

char				*compl_word(int file, char **word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPL WORD ----------");

	t_basic_list		*lst;
	char				*path;
	char				*ret;
	int					i;

	ret = NULL;
	lst = NULL;
	path = NULL;
	i = FALSE;
	add_slash_after_path(word);
	i = complet_var(&lst, &path, word);
	if (!i && ((*word && ft_strchr(*word, '/')) || path))
	{
		if (path == NULL)
			split_path(word, &path);
		get_dircontent(file, path, &lst, *word);
		ft_strdel(&path);
	}
	else if (!i && file == FALSE)
		get_execinpath(file, *word, &lst);
	else if (!i)
		get_dircontent(file, ".", &lst, *word);
	reset_term();
	if (lst)
		launch_select(lst, &ret);
	init_term(FALSE);
	ft_basiclstfree(&lst);
	return (ret);
}
