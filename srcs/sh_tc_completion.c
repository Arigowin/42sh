/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tc_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:49:09 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:16:08 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "libft.h"
#include "ft_select.h"
#include "get_next_line.h"
#define BLANC "\"' \t\n\0"
#define SEP3 "|&;\0"

static void			fork_select(int pfd[2], char **str, t_basic_list *lst)
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

static int			is_file(char *str, int pos, char *word)
{
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

char				*compl_start(char *word, t_basic_list *lst)
{
	char				*start;
	int					i;

	if ((start = ft_strdup(lst->data)) == NULL)
		sh_error(FALSE, 6, NULL, NULL);
	while (lst)
	{
		i = ft_strlen(word);
		while ((lst->data)[i])
		{
			if (i < ft_strlen(start) && (lst->data)[i] != start[i])
				str_charset(&start, '\0', i, ft_strlen(start));
			i++;
		}
		lst = lst->next;
	}
	if (ft_strcmp(word, start) == 0)
	{
		ft_strdel(&start);
		return (NULL);
	}
	return (start);
}

char				*launch_select(t_basic_list *lst, char *word)
{
	int					pfd[2];
	int					nb;
	char				*str;

	str = NULL;
	nb = ft_basiclstcount(lst);
	if (nb == 0)
		return (NULL);
	if (nb == 1)
	{
		if (lst->nb == 4)
			return (str = ft_strjoin(lst->data, "/"));
		return (str = ft_strdup(lst->data));
	}
	if (word && (str = compl_start(word, lst)) != NULL)
		return (str);
	if (nb > 50 && display_or_not(nb) != TRUE)
		return (NULL);
	if (pipe(pfd) == ERROR)
		sh_error(FALSE, 4, NULL, NULL);
	fork_select(pfd, &str, lst);
	check_signal(1);
	return (str);
}

int					fct_tab(char **line, int *pos, t_line *stline,
		t_history **history)
{
	char				*word;
	char				*ret;
	int					i;

	(void)history;
	word = NULL;
	word = get_line(*line, *pos);
	if (word && word[0] == '~' && word[1] != '/')
		fct_insert(line, pos, '/', stline);
	if ((ret = compl_word(is_file(*line, *pos, word), &word)) == NULL)
	{
		ft_strdel(&word);
		return (FALSE);
	}
	i = ft_strlen(word);
	while (ret[i])
	{
		fct_insert(line, pos, ret[i], stline);
		i++;
	}
	ft_strdel(&word);
	ft_strdel(&ret);
	return (TRUE);
}
