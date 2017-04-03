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

static void			enter_key_bis(char ***ret)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- ENTER KEY BIS ----------");

	int					j;
	t_cduo				*tmp;

	j = 0;
	tmp = get_stuff()->lst_param;
	if (tmp->select == TRUE)
	{
		if (((*ret)[j] = ft_strdup(tmp->name)) == NULL)
			return ;
		j++;
	}
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
		{
			if (((*ret)[j] = ft_strdup(tmp->next->name)) == NULL)
				return ;
			j++;
		}
		tmp = tmp->next;
	}
	(*ret)[j] = NULL;
}

char				**enter_key(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- ENTER KEY ----------");

	char				**ret;
	t_cduo				*tmp;
	int					i;

	tmp = get_stuff()->lst_param;
	i = tmp->select;
	ret = NULL;
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
			i++;
		tmp = tmp->next;
	}
	if ((ret = (char **)malloc(sizeof(char*) * (i + 1))) == NULL)
		return (NULL);
	enter_key_bis(&ret);
	return (ret);
}

char				**esc_key(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- ESC KEY ----------");

	termcap_reset();
	return (NULL);
}

int					suppr_key(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- SUPPR KEY ----------");

	t_cduo				*tmp;

	tmp = NULL;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	if (tmp->first == TRUE)
	{
		tmp->next->first = TRUE;
		tmp->next->first_disp = TRUE;
		get_stuff()->lst_param = tmp->next;
	}
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next->cursor = TRUE;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->name);
	free(tmp);
	tmp = NULL;
	get_stuff()->nb_elt -= 1;
	if (get_stuff()->nb_elt == 0)
		esc_key();
	return (0);
}
