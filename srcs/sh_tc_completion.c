#include "shell.h"
#include "libft.h"
#include <sys/types.h>
#include <dirent.h>
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
				ft_basiclstpushbck(list, dp->d_name, dp->d_type);
			}
		}
	}
	closedir(dir);
	return (TRUE);
}

t_basic_list		*get_execinpath(char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET EXECINPATH ----------");

	char				**path;
	char				*tmp;
	int					i;
	t_basic_list		*list;

	list = NULL;
	tmp = get_env("PATH");
	path = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK) != -1)
			get_dircontent(path[i], &list, word);
		i++;
	}
	free_tab(&path);
	return (list);
}

int					compl_exe(char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPL EXE ----------");

	t_basic_list		*lst;
	int					nb;

	nb = 0;
	lst = get_execinpath(word);

	// ANTIBUG
	printf("\nCompletion [%s]\n", word);
	t_basic_list		*tmp = lst;
	while (tmp)
	{
		printf("[%s][%d]\t", tmp->data, tmp->nb);
		tmp = tmp->next;
		nb++;
	}
	printf("\nnb=%d\n", nb);
	// END ANTIBUG

	// ft_select lst_total
	ft_basiclstfree(&lst);
	return (TRUE);
}

int					compl_file(char *word)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- COMPL FILE ----------");

	t_basic_list		*lst;
	char				*path;
	int					nb;
	int					i;


	lst = NULL;
	path = NULL;
	nb = 0;
	i = 0;
	if (ft_strchr(word, '/'))
	{
		// remplacer le tilde par HOME

		i = ft_strlen(word);
		while (i > -1 && word[i] != '/')
			i--;
		path = ft_strsub(word, 0, i + 1);
		word = ft_strsub(word, i + 1, ft_strlen(word) - i);

		printf("\npath[%s]word[%s]\n", path, word);

		get_dircontent(path, &lst, word);
		ft_strdel(&path);
	}
	else
		get_dircontent(".", &lst, word);

	// ANTIBUG
	printf("\nCompletion [%s]\n", word);
	t_basic_list		*tmp = lst;
	while (tmp)
	{
		printf("[%s][%d]\t", tmp->data, tmp->nb);
		tmp = tmp->next;
		nb++;
	}
	printf("\nnb=%d\n", nb);
	// END ANTIBUG

	// ft_select lst_total
	ft_basiclstfree(&lst);
	return (TRUE);
}

int					fct_tab(char **str, int *pos, t_line *stline,
		t_history **history)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- FCT TAB ----------");

	char				*word;

	(void)stline;
	(void)history;
	word = NULL;
	word = get_line(*str, *pos);
	if (is_file(*str, *pos, word) == TRUE)
		compl_file(word);
	else
		compl_exe(word);
	ft_strdel(&word);
	return (TRUE);
}

/*
 **	liste de l'auto completion par defaut de bash(builtin principalement)
 :
 [
 {
 bg
 builtin
 cd
 complete
 coproc
 disown
 echo
 enable
 exec
 false
 fi
 getopts
 history
 jobs
 local
 popd
 pwd
 readonly
 set
 source
 then
 trap
 typeset
 unalias
 wait
 !
 [[
 }
 bind
 caller
 command
 compopt
 declare
 do
 elif
 esac
 exit
 fc
 for
 hash
 if
 kill
 logout
 printf
 read
 return
 shift
 suspend
 time
 true
 ulimit
 unset
 while
 .
 ]]
 alias
 break
 case
 compgen
 continue
 dirs
 done
 else
 eval
 export
 fg
function
help
in
let
mapfile
pushd
readarray
select
shopt
test
times
type
umask
until
*/
