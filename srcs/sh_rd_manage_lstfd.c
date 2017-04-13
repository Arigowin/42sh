/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rd_manage_lstfd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:48:53 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:48:54 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

t_lst_fd			*lstfd_new(int fd, char *filename)
{
	t_lst_fd			*new_fd;

	if ((new_fd = (t_lst_fd*)malloc(sizeof(t_lst_fd))) == NULL)
	{
		sh_error(FALSE, 6, NULL, NULL);
		return (NULL);
	}
	new_fd->fd = fd;
	if ((new_fd->filename = ft_strdup(filename)) == NULL)
	{
		sh_error(FALSE, 6, NULL, NULL);
		return (NULL);
	}
	new_fd->next = NULL;
	return (new_fd);
}

int					lstfd_pushfront(t_lst_fd **lstfd, int fd, char *filename)
{
	t_lst_fd			*new_fd;

	new_fd = NULL;
	if (lstfd && !(*lstfd))
		*lstfd = lstfd_new(fd, filename);
	else
	{
		new_fd = lstfd_new(fd, filename);
		new_fd->next = *lstfd;
		*lstfd = new_fd;
	}
	return (TRUE);
}

int					del_lstfd(t_lst_fd **lstfd)
{
	t_lst_fd			*tmpfd;

	tmpfd = NULL;
	while (lstfd && *lstfd)
	{
		tmpfd = *lstfd;
		*lstfd = (*lstfd)->next;
		ft_strdel(&(tmpfd->filename));
		free(tmpfd);
		tmpfd = NULL;
	}
	lstfd = NULL;
	return (TRUE);
}

int					close_lstfd(t_lst_fd **lstfd)
{
	t_lst_fd			*tmp;

	tmp = NULL;
	if (lstfd)
	{
		while (lstfd && *lstfd)
		{
			if ((*lstfd)->fd > 2)
				close((*lstfd)->fd);
			ft_strdel(&((*lstfd)->filename));
			tmp = *lstfd;
			*lstfd = (*lstfd)->next;
			free(tmp);
			tmp = NULL;
		}
		*lstfd = NULL;
	}
	return (TRUE);
}

int					push_in_lstfd(t_node *tree, t_lst_fd **lstfd, int fd,
					int *fd_save)
{
	char				*filename;

	if (*fd_save == -1)
	{
		if (fd >= 0)
			close(fd);
		fd = -1;
	}
	*fd_save = fd;
	if (tree && (tree->type == RRED || tree->type == DRRED || tree->type == LRED
	|| tree->type == RWRED) && tree->right)
	{
		filename = (tree->right->type == RED_ARG ?
				ft_strdup_ignchar(tree->right->data, '\\')
				: ft_strdup_ignchar(tree->right->right->data, '\\'));
		lstfd_pushfront(lstfd, fd, filename);
		ft_strdel(&filename);
		if (fd == -1)
			return (FALSE);
	}
	return (TRUE);
}
