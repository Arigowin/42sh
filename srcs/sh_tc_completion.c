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

int					insert_cmp(char *s1, char *s2)
{
	const unsigned char		*tmp_s1;
	const unsigned char		*tmp_s2;

	tmp_s1 = (const unsigned char*)s1;
	tmp_s2 = (const unsigned char*)s2;
	while (*tmp_s1 == *tmp_s2 && *tmp_s1 != '\0')
	{
		tmp_s1++;
		tmp_s2++;
	}
	if (*tmp_s1 && *tmp_s1 != *tmp_s2 && ft_isalnum(*tmp_s1) == 0
			&& ft_isalnum(*tmp_s2) == 1)
		return (-1);
	else if (*tmp_s1 && *tmp_s1 != *tmp_s2 && ft_isalnum(*tmp_s1) != 0
			&& ft_isalnum(*tmp_s2) == 0)
		return (1);
	return (*tmp_s1 - *tmp_s2);
}

int					cmp_dupli(char *s1, char *s2)
{
	int					cmp;
	char				*tmp1;
	char				*tmp2;
	int					dot1;
	int					dot2;

	dot1 = FALSE;
	dot2 = FALSE;
	if (s1[0] == '.')
		dot1 = TRUE;
	if (s2[0] == '.')
		dot2 = TRUE;
	tmp1 = (dot1 ? ft_strdup(++s1) : ft_strdup(s1));
	tmp2 = (dot2 ? ft_strdup(++s2) : ft_strdup(s2));
	cmp = insert_cmp(str_toupper(tmp1), str_toupper(tmp2));
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	if (cmp == 0)
	{
		if (dot1 != TRUE && dot2 != TRUE)
			cmp = insert_cmp(s1, s2);
		else if (dot2)
			cmp = -1;
		else if (dot1)
			cmp = 1;
	}
	return (cmp);
}

int					sort_first(t_basic_list **lst, char *name, int type)
{
	t_basic_list		*tmp;
	int					cmp;

	cmp = cmp_dupli((*lst)->data, name);
	if (cmp == 0)
		return (0);
	if (cmp > 0)
	{
		tmp = (*lst);
		(*lst) = ft_basiclstnew(name, type);
		(*lst)->next = tmp;
		return (0);
	}
	else
	{
		if ((*lst)->next && cmp_dupli((*lst)->next->data, name) > 0)
		{
			tmp = (*lst)->next;
			(*lst)->next = ft_basiclstnew(name, type);
			(*lst)->next->next = tmp;
			return (0);
		}
	}
	return (1);
}

int					insert_sort(t_basic_list **ite, char *name, int type)
{
	t_basic_list		*tmp;
	int					cmp;

	cmp = cmp_dupli((*ite)->next->data, name);
	if (cmp == 0)
		return (0);
	else if (cmp > 0)
	{
		tmp = (*ite)->next;
		(*ite)->next = ft_basiclstnew(name, type);
		(*ite)->next->next = tmp;
		return (0);
	}
	else if (cmp < 0)
	{
		if ((*ite)->next->next && cmp_dupli((*ite)->next->next->data, name) > 0)
		{
			tmp = ft_basiclstnew(name, type);
			tmp->next = (*ite)->next->next;
			(*ite)->next->next = tmp;
			return (0);
		}
	}
	return (1);
}

void				sort_push(t_basic_list **lst, char *name, int type)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- SORT PUSHBCK ----------");

	t_basic_list		*ite;

	ite = *lst;
	if (ite)
	{
		if (sort_first(lst, name, type) == 0)
			return ;
	}
	while (ite && ite->next)
	{
		if (insert_sort(&ite, name, type) == 0)
			return ;
		ite = ite->next;
	}
	ft_basiclstpushbck(lst, name, type);
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

int					fill_list_compl(char *word, t_basic_list **lst)
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

static void				fork_select(int pfd[2], char **str, t_basic_list *lst)
{
	pid_t				pid;

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
		ft_strdel(str);
		get_next_line(pfd[0], str);
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
	int					nb;

	nb = ft_basiclstcount(lst);
	if (nb == 0)
		return (NULL);
	else if (nb == 1)
	{
		if (lst->nb == 4)
			return (*str = ft_strjoin(lst->data, "/"));
		return (*str = ft_strdup(lst->data));
	}
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

int					parse_tilde(char **path)
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

int					split_path(char **word, char **path)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- SPLIT PATH ----------");

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

void				add_slash_after_path(char **word)
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
	if (word && word[0] == '~' && word[1] != '/')
		fct_insert(str, pos, '/', stline);
	if ((ret = compl_word(is_file(*str, *pos, word), &word)) == NULL)
	{
		ft_strdel(&word);
		return (FALSE);
	}
	i = ft_strlen(word);
	while (ret[i])
	{
		fct_insert(str, pos, ret[i], stline);
		i++;
	}
	ft_strdel(&word);
	ft_strdel(&ret);
	return (TRUE);
}
