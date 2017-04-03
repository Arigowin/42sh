/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:29 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_select.h"
#include "libft.h"

int				manage_error(int i)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- MANAGE ERROR ----------");

	if (i == 1)
	{
		ft_putendl("ft_select: can't initialize termcap");
		termcap_reset();
	}
	if (i == 2)
		ft_putendl("ft_select: usage: ./ft_select arg_1 [arg_2] [...] [arg_n]");
	exit(EXIT_FAILURE);
	return (-1);
}

void			free_lst_param(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- FREE LST PARAM ----------");

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

int				ft_select(t_basic_list *lst)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- FT SELECT ----------");

	t_cduo				*lst_param;
	char				**ret;

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
	if (ret != NULL)
		print_return(&ret);
	return (0);
}
