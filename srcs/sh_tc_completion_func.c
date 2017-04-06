#include "shell.h"
#include "libft.h"
#include "ft_select.h"

static int			parse_tilde(char **path)
{
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

static int			split_path(char **word, char **path)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("--------- SPLIT PATH ----------");

	char				*tmp;
	int					i;

	i = ft_strlen(*word);
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

static void			add_slash_after_path(char **word)
{
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

char				*compl_word(int file, char **word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPL WORD ----------");

	t_basic_list		*lst;
	char				*path;
	char				*ret;

	ret = NULL;
	lst = NULL;
	path = NULL;
	add_slash_after_path(word);
	if (*word && (*word)[0] == '$')
	{
		get_varlist(&lst, word);
	}
	else if (ft_strchr(*word, '/'))
	{
		split_path(word, &path);
		get_dircontent(file, path, &lst, *word);
		ft_strdel(&path);
	}
	else if (file == FALSE)
		get_execinpath(file, *word, &lst);
	else
		get_dircontent(file, ".", &lst, *word);
	reset_term();
	if (lst)
		launch_select(lst, &ret);
	init_term(FALSE);
	ft_basiclstfree(&lst);
	return (ret);
}
