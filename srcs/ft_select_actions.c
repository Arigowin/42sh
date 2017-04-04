/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:28 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:28 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

char				*enter_key(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- ENTER KEY ----------");

	char				*ret;
	t_cduo				*tmp;
	//int					i;

	tmp = get_stuff()->lst_param;
	ret = NULL;
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
			break ;
		tmp = tmp->next;
	}
	if ((ret = ft_strdup(tmp->next->name)) == NULL)
		return (NULL);
	return (ret);
}

char				*esc_key(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- ESC KEY ----------");

	termcap_reset();
	return (NULL);
}
