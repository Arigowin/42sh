#include "shell.h"
#include "libft.h"
#include <sys/types.h>
#include <dirent.h>

char				*get_line(char *str, int pos)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET LINE ----------");

	char				*ret;
	int					i;

	ret = NULL;
	i = pos;
	pos--;
	while (ft_strchr(SEP, str[pos]) == NULL)
		pos--;
	if (pos == i - 1)
		return (NULL);
	pos++;
	ret = ft_strsub(str, pos, i - pos);
	return (ret);
}

int					get_dircontent(char *path, t_list **list)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET DIRCONTENT ----------");

	struct dirent		*dp;
	DIR					*dir;

	dir = opendir(path);
	while ((dp = readdir(dir)) != NULL)
	{
		if (*list == NULL)
			*list = ft_lstnew(dp->d_name);
		else
			ft_lstadd(list, ft_lstnew(dp->d_name));

		// implementer une liste chainer pour stocker les nom des fichier/dossiers
//		printf("[%s]\t", dp->d_name);
//		if (dp->d_type == 4)
//			printf("%d DIR\n", dp->d_type);
//		else
//			printf("%d FILE\n", dp->d_type);
	}
	closedir(dir);
	return (TRUE);
}

t_list				*get_execinpath()
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- GET EXECINPATH ----------");

	char				**path;
	char				*tmp;
	int					i;
	t_list				*list;

	list = NULL;
	tmp = get_env("PATH");
	path = ft_strsplit(tmp, ':');
	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK) != -1)
			get_dircontent(path[i], &list);
		i++;
	}
	return (list);
}

int					fct_tab(char **str, int *pos, t_line *stline,
					t_history **history)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- FCT TAB ----------");

	char				*word;
	t_list				*lst_total;
	t_list				*lst_final;

	(void)stline;
	(void)history;
	word = NULL;
	lst_final= NULL;
	lst_total = get_execinpath();
	word = get_line(*str, *pos);
	if ((*str)[0] == '\0' || word == NULL)
	{
		printf("\nlist de tout les exe\n");
		while (lst_total)
		{
			printf("[%s]\t", lst_total->content);
			lst_total = lst_total->next;
		}
		printf("\n");
	}
	else
	{
		printf("\nCompleter[%s]\n", word);
		while (lst_total)
		{
			if (ft_strncmp(word, lst_total->content, ft_strlen(word)) == 0)
			{
				if (lst_final == NULL)
					lst_final = ft_lstnew(lst_total->content);
				else
					ft_lstadd(&lst_final, ft_lstnew(lst_total->content));
				printf("[%s]\t", lst_total->content);
			}
			lst_total = lst_total->next;
		}
		printf("\n");
	}

	// recuperer se qu'il ya sur la lgne depuis le dernier SEP
	// si qqchose faire un readdir du dossier courant et chercher une/des correspondances
	// sinon lister le dossier courant si pas au debut sinon PATH

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
./
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
