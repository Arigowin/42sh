#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "shell.h"
#include "libft.h"
#include "ft_select.h"
#include "get_next_line.h"
# define SEP2 "|&;><\"' \t\n\0"
#define SEP3 "|&;\0"
#define BLANC "\"' \t\n\0"

char				*get_line(char *str, int pos)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET LINE ----------");

	int					i;

	i = pos;
	pos--;
	while (pos > -1 && ft_strchr(SEP2, str[pos]) == NULL)
		pos--;
	if (pos == i - 1)
		return (NULL);
	pos++;
	return (ft_strsub(str, pos, i - pos));
}

int					is_file(char *str, int pos, char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- IS FILE ----------");

	if (ft_strchr(word, '/'))
		return (TRUE);
	if (ft_strlen(str) == 0)
		return (FALSE);
	pos -= ft_strlen(word) + 1;
	if (pos <= 0)
		return (FALSE);
	while (pos > -1 && ft_strchr(BLANC, str[pos]) != NULL)
		pos--;
	if (ft_strchr(SEP3, str[pos]) != NULL)
		return (FALSE);
	return (TRUE);
}

void				sort_pushbck(t_basic_list **lst, char *name, int type)
{
	//if (DEBUG_COMPL == 1)
		ft_putendl("---------- SORT PUSHBCK ----------");

	t_basic_list		*tmp;

	tmp = *lst;
	while (tmp)
	{
	}
}

int					get_dircontent(char *path, t_basic_list **list, char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET DIRCONTENT ----------");

	struct dirent		*dp;
	DIR					*dir;

	dir = opendir(path);
	while (dir && (dp = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dp->d_name, ".") != 0 && ft_strcmp(dp->d_name, "..") != 0)
		{
			// type 4 == DIR
			if (word == NULL || ft_strncmp(word, dp->d_name, ft_strlen(word)) == 0)
			{
				// NE PAS SAUVEGARDER LES DOUBLON !!!
				// par exemple
				// si il ya 2 ls un dans /bin et l'autre dans /usr/bin
				// et le PATH=/usr/bin:/bin
				// le ls qui est dans /usr/bin sera utiliser

				// FAIRE UN TRIE PAR INSERTION
				sort_pushbck(list, dp->d_name, dp->d_type);
				//ft_basiclstpushbck(list, dp->d_name, dp->d_type);
			}
		}
	}
	closedir(dir);
	return (TRUE);
}

int					fill_list_compl(char *word, t_basic_list **lst)
{
	static char			*def[10] = {".", "cd", "echo", "env", "exit",
		"export", "setenv", "unset", "unsetenv", NULL};
	int					i;
	int					type;

	i = 0;
	while (def[i])
	{
		if (word == NULL || ft_strncmp(word, def[i], ft_strlen(word)) == 0)
		{
			type = (i == 0 ? 4 : 0);
			ft_basiclstpushbck(lst, def[i], type);
		}
		i++;
	}
	return (TRUE);
}

int					get_execinpath(char *word, t_basic_list **lst)
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
			get_dircontent(path[i], lst, word);
		i++;
	}
	free_tab(&path);
	return (TRUE);
}

static void				fork_select(int pfd[2], char **str, t_basic_list *lst)
{
	pid_t				pid;
	char				*line;

	line = NULL;
	if ((pid = fork()) < 0)
		sh_error(FALSE, 5, NULL, NULL);
	if (pid == 0)
	{
		check_signal(2);
		close(pfd[0]);
		*str = ft_select(lst);
		write(pfd[1], *str, ft_strlen(*str));
		exit(EXIT_SUCCESS);
	}
	else
	{
		check_signal(3);
		close(pfd[1]);
		while (get_next_line(pfd[0], &line) > 0)
			*str = ft_strdup(line);
		wait(NULL);
		close(pfd[0]);
		reset_std_fd();
	}
}

char				*launch_select(t_basic_list *lst, char **str)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- LAUNCH SELECT ----------");

	int					pfd[2];
	reset_term();
	if (pipe(pfd) == ERROR)
	{
		sh_error(FALSE, 4, NULL, NULL);
		return (NULL);
	}
	fork_select(pfd, str, lst);
	init_term(FALSE);
	check_signal(1);
	return (*str);
}

int					split_path(char **word, char **path)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- SPLIT PATH ----------");

	char				*tmp;
	int					i;

	// remplacer le tilde par HOME
	i = ft_strlen(*word);
	while (i > -1 && (*word)[i] != '/')
		i--;
	*path = ft_strsub(*word, 0, i + 1);
	tmp = ft_strsub(*word, i + 1, ft_strlen(*word) - i);
	ft_strdel(word);
	*word = ft_strdup(tmp);
	ft_strdel(&tmp);

	//printf("\npath[%s]word[%s]\n", *path, *word);
	return (TRUE);
}

char				*compl_word(int f, char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPL WORD ----------");

	t_basic_list		*lst;
	char				*path;
	char				*ret;

	ret = NULL;
	lst = NULL;
	path = NULL;
	if (ft_strchr(word, '/'))
	{
		split_path(&word, &path);
		get_dircontent(path, &lst, word);
		ft_strdel(&path);
	}
	else if (f == FALSE)
		get_execinpath(word, &lst);
	else
		get_dircontent(".", &lst, word);
	reset_term();
	if (lst)
		launch_select(lst, &ret);
	init_term(FALSE);
	ft_basiclstfree(&lst);
	return (ret);
}

int					fct_tab(char **str, int *pos, t_line *stline,
		t_history **history)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- FCT TAB ----------");

	char				*word;
	char				*ret;
	int					i;

	(void)history;
	word = NULL;
	word = get_line(*str, *pos);
	if ((ret = compl_word(is_file(*str, *pos, word), word)) == NULL)
		return (FALSE);
	i = ft_strlen(word);
	while (ret[i])
	{
		fct_insert(str, pos, ret[i], stline);
		i++;
	}
	ft_strdel(&word);
	return (TRUE);
}
