/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_father_n_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:56 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:14:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"
#include "libft.h"

static int			father(int pipefd_tab[2][2])
{
	int					stat_loc;

	stat_loc = 0;
	check_signal(3);
	pfd_close(pipefd_tab);
	if (pipefd_tab[1][0] < 0)
		while (waitpid(-1, &stat_loc, WNOHANG) >= 0)
			;
	if (WIFSIGNALED(stat_loc))
		return (-2);
	if (WIFEXITED(stat_loc) != TRUE)
		return (ERROR);
	return (WEXITSTATUS(stat_loc));
}

static int			son(char **cmd, int pipefd_tab[2][2], t_node *tree,
					t_lst_fd **lstfd)
{
	int					ret;
	int					fd;

	fd = (lstfd && *lstfd && tree->left ? (*lstfd)->fd : -2);
	ret = TRUE;
	pfd_handler(pipefd_tab);
	if ((pipefd_tab[0][0] >= 0 || pipefd_tab[1][0] >= 0) && tree && tree->left
	&& lstfd && *lstfd && !(ret = redirect(tree->left, *lstfd)))
	{
		if (ret == ERROR)
			exit_pgm(EXIT_FAILURE);
		if (ret == FALSE)
			exit_pgm(EXIT_SUCCESS);
	}
	if (lstfd && check_builtin(fd, cmd, lstfd) == TRUE)
		exit(EXIT_SUCCESS);
	check_signal(2);
	if (check_fct(fd, cmd) == -2)
		exit_pgm(EXIT_FAILURE);
	return (sh_error(FALSE, 24, cmd[0], NULL));
}

int					handle_fork(int pipefd_tab[2][2], t_node *tree,
					t_lst_fd **lstfd, char **cmd)
{
	int					fct_ret;
	pid_t				fpid;

	fpid = -1;
	fct_ret = -100;
	reset_term();
	if ((fpid = fork()) < 0)
		sh_error(FALSE, 5, NULL, NULL);
	if (fpid == 0)
		son(cmd, pipefd_tab, tree, lstfd);
	else
		fct_ret = father(pipefd_tab);
	savior_fct_ret(fct_ret, TRUE);
	init_term(FALSE);
	return (TRUE);
}
