#include <term.h>
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

int					init_getdircontent(t_basic_list **lst, char **path,
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

int					check_yn(int key, t_line *stline)
{
	int					i;

	ft_putchar(key);
	if (key != RETURN)
		ft_putchar('\n');
	tputs(tgetstr("up", NULL), 1, my_outc);
	tputs(tgetstr("ce", NULL), 1, my_outc);
	tputs(tgetstr("up", NULL), 1, my_outc);
	i = 0;
	while (i < stline->curs_x)
	{
		tputs(tgetstr("nd", NULL), 1, my_outc);
		i++;
	}
	check_signal(1);
	if (key == 'y' || key == 'Y' || key == RETURN || key == TAB)
		return (TRUE);
	else
		return (FALSE);
}

int					display_or_not(int nb)
{
	t_line				*stline;
	int					key;
	int					ret;

	init_term(FALSE);
	check_signal(4);
	ft_putstr("\nDisplay all ");
	ft_putnbr(nb);
	ft_putstr(" possibilities? (y or n) ");
	stline = savior_stline(NULL, FALSE);
	while ((ret = read(STDIN_FILENO, &key, sizeof(int))) > 0)
	{
		if (key == 'y' || key == 'Y' || key == 'n' || key == 'N'
				|| key == TAB || key== RETURN)
		{
			if (check_yn(key, stline) == TRUE)
				break;
			return (FALSE);
		}
		key = 0;
	}
	ctrl_c_hrd(stline, TRUE);
	if (ret < 0)
		return (ERROR);
	return (TRUE);
}
