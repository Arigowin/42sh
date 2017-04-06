#include <dirent.h>
#include "shell.h"
#include "libft.h"
#include "ft_select.h"

static int			fill_list_compl(char *word, t_basic_list **lst)
{
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

int					get_dircontent(int file, char *path, t_basic_list **list, char *word)
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
			if (word == NULL || ft_strncmp(word, dp->d_name, ft_strlen(word)) == 0)
				sort_push(list, dp->d_name, dp->d_type);
		}
	}
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
	tmp = get_env("PATH");
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

int					get_varlist(t_basic_list **lst, char **word)
{
	t_duo				*env;
	char				*tmp;

	tmp = ft_strdup(srch_value(*word, '$'));
	ft_strdel(word);
	*word = ft_strdup(tmp);
	ft_strdel(&tmp);
	env = savior_env(NULL, FALSE);
	while (env)
	{
		if (ft_strlen(*word) == 0 ||
				ft_strncmp(*word, env->name, ft_strlen(*word)) == 0)
			sort_push(lst, env->name, 0);
		env = env->next;
	}
	return (TRUE);
}
