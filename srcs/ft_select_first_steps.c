/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:28 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:28 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include "ft_select.h"
#include "libft.h"

int				ft_putchr(int c)
{
	int					fd;

	fd = get_stuff()->fd;
	write(fd, &c, 1);
	return (0);
}

void			clr_screen(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- CLR SCREEN ----------");

	char				*str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, ft_putchr);
}

int				fill_list(t_cduo **lst_param, t_basic_list *lst)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- FILL LIST ----------");

	char				*tmp;
	int					i;
	int					len;
	int					max_len;

	i = 0;
	len = 0;
	max_len = 0;
	while (lst)
	{
		if (lst->nb == 4)
			cduo_pushback(lst_param, (tmp = ft_strjoin(lst->data, "/")), i);
		else
			cduo_pushback(lst_param, lst->data, i);
		ft_strdel(&tmp);
		len = ft_strlen(lst->data);
		if (len > 40)
			max_len = 40;
		else if (max_len < len)
			max_len = len;
		i++;
		lst = lst->next;
	}
	get_stuff()->nb_elt = i - 1;
	get_stuff()->lst_param = *lst_param;
	return (max_len);
}

static char		*get_input(int buff)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- GET INPUT ----------");

	char				*ret;

	ret = NULL;
	if (buff == DOWN_ARROW)
		down_arrow(0);
	if (buff == UP_ARROW)
		up_arrow();
	if (buff == ESCAPE || buff == 'q')
		ret = esc_key();
	if (buff == RETURN || buff == TAB)
	{
		down_arrow(1);
		ret = enter_key();
	}
	return (ret);
}

char			*select_read(void)
{
	if (DEBUG_FT_SELECT == 1)
		ft_putendl("---------- SELECT READ ----------");

	int					buff;
	char				*ret;

	buff = 0;
	ret = NULL;
	if (read(0, &buff, 4) == -1)
		return (NULL);
	ret = get_input(buff);
	return (ret);
}
