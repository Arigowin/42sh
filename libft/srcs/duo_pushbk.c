/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duo_pushback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:47:52 by avacher           #+#    #+#             */
/*   Updated: 2017/01/21 19:16:33 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_duo		*duo_new(char *name, char *val, t_env type)
{
	t_duo				*new;

	if ((new = (t_duo *)malloc(sizeof(t_duo))) == NULL)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->tmp_val = NULL;
	new->type = type;
	new->next = NULL;
	if (name && (new->name = ft_strdup(name)) == NULL)
		return (NULL);
	if (val && (new->value = ft_strdup(val)) == NULL)
		return (NULL);
	return (new);
}

int					duo_pushback(t_duo **lst, char *name, char *val, t_env type)
{
	t_duo				*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		if ((*lst = duo_new(name, val, type)) == NULL)
			return (-1);
		return (0);
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((tmp->next = duo_new(name, val, type)) == NULL)
		return (-1);
	return (0);
}
