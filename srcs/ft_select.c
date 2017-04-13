/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2017/04/13 17:36:13 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"
#include "libft.h"

int				manage_error(int i)
{
	if (i == 1)
	{
		ft_putendl("\nft_select: can't initialize termcap");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
	return (-1);
}

void			free_lst_param(void)
{
	t_cduo				*tmp;

	tmp = NULL;
	if (get_stuff()->nb_elt && get_stuff()->lst_param)
		get_stuff()->lst_param->prev->next = NULL;
	while (get_stuff()->nb_elt && get_stuff()->lst_param)
	{
		tmp = get_stuff()->lst_param;
		get_stuff()->lst_param = get_stuff()->lst_param->next;
		tmp->prev = NULL;
		free(tmp->name);
		free(tmp);
	}
}

char			*select_read(void)
{
	int					buff;
	int					ret_r;
	char				*ret;

	buff = 0;
	ret_r = 0;
	ret = NULL;
	while ((ret_r = read(0, &buff, 4)) > 0)
	{
		ret = get_input(buff);
		break ;
	}
	if (ret_r < 0)
		return (NULL);
	return (ret);
}

char			*ft_select(t_basic_list *lst)
{
	t_cduo				*lst_param;
	char				*ret;

	lst_param = NULL;
	ret = NULL;
	if (termcap_init() == -1)
		manage_error(1);
	get_stuff()->max_len = fill_list(&lst_param, lst);
	while (1)
	{
		clr_screen();
		manage_columns();
		if ((ret = select_read()) != NULL)
			break ;
	}
	termcap_reset();
	return (ret);
}
