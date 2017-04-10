#include <dirent.h>
#include "shell.h"
#include "libft.h"

static int			fill_list_compl(char *word, t_basic_list **lst)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- FILL LIST COMPL ----------");

	static char			*def[11] = {".", "..", "cd", "echo", "env", "exit",
		"export", "setenv", "unset", "unsetenv", NULL};
	int					i;
	int					type;

	i = 0;
	while (def[i])
	{
		if (word == NULL || ft_strncmp(word, def[i], ft_strlen(word)) == 0)
		{
			type = (i <= 1 ? 4 : 0);
			sort_push(lst, def[i], type);
		}
		i++;
	}
	return (TRUE);
}

int					get_dircontent(int file, char *path, t_basic_list **list,
		char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET DIRCONTENT ----------");

	struct dirent		*dp;
	DIR					*dir;

	dir = opendir(path);
	while (dir && (dp = readdir(dir)) != NULL)
	{
		if (file || (ft_strcmp(dp->d_name, ".") != 0
					&& ft_strcmp(dp->d_name, "..") != 0))
		{
			if (word == NULL ||
					ft_strncmp(word, dp->d_name, ft_strlen(word)) == 0)
				sort_push(list, dp->d_name, dp->d_type);
		}
	}
	if (dir)
		closedir(dir);
	return (TRUE);
}

int					get_execinpath(int file, char *word, t_basic_list **lst)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET EXECINPATH ----------");

	char				**path;
	char				*tmp;
	int					i;

	path = NULL;
	tmp = get_env("PATH", BOTH);
	if (tmp)
		path = ft_strsplit(tmp, ':');
	fill_list_compl(word, lst);
	ft_strdel(&tmp);
	i = 0;
	while (path && path[i])
	{
		if (access(path[i], F_OK) != -1)
			get_dircontent(file, path[i], lst, word);
		i++;
	}
	free_tab(&path);
	return (TRUE);
}

int					browse_and_add_var(t_basic_list **lst, t_duo *var,
		char *word)
{
	while (var)
	{
		if (ft_strlen(word) == 0 ||
				ft_strncmp(word, var->name, ft_strlen(word)) == 0)
		{
			sort_push(lst, var->name, 0);
		}
		var = var->next;
	}
	return (TRUE);
}

int					get_varlist(t_basic_list **lst, char **word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET VARLIST ----------");

	char				*tmp;

	if ((tmp = ft_strdup(srch_value(*word, '$'))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	ft_strdel(word);
	if ((*word = ft_strdup(tmp)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	ft_strdel(&tmp);
	browse_and_add_var(lst, savior_env(NULL, FALSE), *word);
	browse_and_add_var(lst, savior_local(NULL, FALSE), *word);
	return (TRUE);
}
