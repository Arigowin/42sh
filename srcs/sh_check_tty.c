/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_tty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:55 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:13:40 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "get_next_line.h"

static int			checktty_tool2(t_line *stline, char *line)
{
	int					std_fd[3];
	int					std;

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	std_fd[2] = dup(STDERR_FILENO);
	ft_strdel(&(stline->line));
	if ((stline->line = ft_strdup(line)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	if (check_after_read(stline, NULL) == ERROR)
		return (ERROR);
	std = -1;
	while (++std <= STDERR_FILENO)
	{
		dup2(std_fd[std], std);
		close(std_fd[std]);
	}
	return (TRUE);
}

static int			checktty_tool(t_line *stline)
{
	char				*line;
	int					ret;

	ret = 0;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_isstrascii(line) == 0)
			return (error_clear_dblstr(ERROR, 37, &line, NULL));
		if (checktty_tool2(stline, line) == ERROR)
			return (ERROR);
		ft_strdel(&line);
	}
	if (line)
	{
		if (ft_isstrascii(line) == 0)
			return (error_clear_dblstr(ERROR, 37, &line, NULL));
		if (checktty_tool2(stline, line) == ERROR)
			return (ERROR);
	}
	ft_strdel(&line);
	if (ret == ERROR)
		return (ERROR);
	return (TRUE);
}

int					checktty(t_line *stline)
{
	if (!isatty(0))
	{
		checktty_tool(stline);
		exit_clear_stline(savior_fct_ret(0, FALSE), &stline);
	}
	return (TRUE);
}
