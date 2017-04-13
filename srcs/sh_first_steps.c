/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_first_steps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:57 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:40:48 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static char			*get_path(void)
{
	char				*path;
	char				*tmp;
	char				*home;

	home = get_env("HOME", ENV, TRUE);
	if ((path = get_env("PWD", ENV, TRUE)) == NULL)
		return (NULL);
	tmp = ft_strsub(path, 0, ft_strlen(home));
	if (home && ft_strlen(home) > 0 && ft_strcmp(home, tmp) == 0)
	{
		ft_strdel(&tmp);
		tmp = ft_strsub(path, ft_strlen(home), ft_strlen(path));
		ft_strdel(&path);
		path = ft_properjoin("~", tmp);
	}
	ft_strdel(&home);
	ft_strdel(&tmp);
	return (path);
}

int					miniprt_reset_stline(t_line *stline)
{
	ft_putstr("> ");
	stline->curs_x = 2;
	stline->curs_y = 0;
	stline->mini_prt = TRUE;
	return (TRUE);
}

int					mini_prt_handler(char **str, int *pos, t_line *stline)
{
	if ((*str)[0] != '\0')
		fct_insert(str, pos, '\n', stline);
	else if (!ft_strcmp(*str, ""))
		fct_insert(str, pos, '\n', stline);
	else if (quote_is_close(str) == 0)
		fct_insert(str, pos, '\n', stline);
	miniprt_reset_stline(stline);
	return (CONTINUE);
}

int					display_prompt(void)
{
	char				*name;
	char				*path;
	char				*shlvl;

	path = get_path();
	name = get_env("LOGNAME", ENV, TRUE);
	if (name)
		ft_putstr_color("\033[34;1m", name);
	if ((shlvl = get_env("SHLVL", ENV, TRUE)))
	{
		ft_putchar_color("\033[31m", '[');
		ft_putstr_color("\033[31m", shlvl);
		ft_putchar_color("\033[31m", ']');
	}
	if ((name || shlvl) && path)
		ft_putstr(":");
	if (path)
		ft_putstr_color("\033[32;1m", path);
	if (path || name)
		ft_putchar('\n');
	ft_putstr_color("\033[36m", "> ");
	ft_strdel(&name);
	ft_strdel(&path);
	ft_strdel(&shlvl);
	return (TRUE);
}

int					fill_path(t_duo **env)
{
	char				*tmp;

	tmp = NULL;
	if (!get_env("PATH", ENV, TRUE) && duo_pushback(env, "PATH",
	"/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.",
	ENV) == ERROR)
		return (sh_error(FALSE, 6, NULL, NULL));
	if (get_env("PWD", ENV, TRUE) == NULL)
	{
		if ((tmp = getcwd(tmp, MAX_PATH)) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		if (duo_pushback(env, "PWD", tmp, ENV) == ERROR)
			return (sh_error(FALSE, 6, NULL, NULL));
		ft_strdel(&tmp);
	}
	if (!get_env("TERM", ENV, TRUE)
	&& duo_pushback(env, "TERM", "xterm", ENV) == ERROR)
		return (sh_error(FALSE, 6, NULL, NULL));
	return (TRUE);
}
