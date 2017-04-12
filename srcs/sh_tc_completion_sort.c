#include "shell.h"
#include "libft.h"
#include "ft_select.h"

/*
** compare 2 chaines
** en quoi il insert ?
*/
/*
static int				insert_cmp(char *s1, char *s2)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- INSERT CMP ----------");

	const unsigned char		*tmp_s1;
	const unsigned char		*tmp_s2;

	tmp_s1 = (const unsigned char*)s1;
	tmp_s2 = (const unsigned char*)s2;
	while (*tmp_s1 == *tmp_s2 && *tmp_s1 != '\0')
	{
		tmp_s1++;
		tmp_s2++;
	}
	if (*tmp_s1 && *tmp_s1 != *tmp_s2 && ft_isalnum(*tmp_s1) == 0
			&& ft_isalnum(*tmp_s2) == 1)
		return (-1);
	// t'as pas voulu dire plutot *tmp_s2 && .. isalnum s1 == 1 ?
	else if (*tmp_s1 && *tmp_s1 != *tmp_s2 && ft_isalnum(*tmp_s1) != 0
			&& ft_isalnum(*tmp_s2) == 0)
		return (1);
	return (*tmp_s1 - *tmp_s2);
}

static int				cmp_dupli(char *s1, char *s2)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- CMP DUPLI ----------");

	int					cmp;
	char				*tmp1;
	char				*tmp2;
	int					dot1;
	int					dot2;

	dot1 = (s1[0] == '.');
	dot2 = (s2[0] == '.');
	if ((tmp1 = (dot1 ? ft_strdup(++s1) : ft_strdup(s1))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	if ((tmp2 = (dot2 ? ft_strdup(++s2) : ft_strdup(s2))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	cmp = insert_cmp(str_toupper(tmp1), str_toupper(tmp2));
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	if (cmp == 0)
	{
		cmp = (dot1 != TRUE && dot2 != TRUE ? insert_cmp(s1, s2) : cmp);
		cmp = (cmp == 0 && dot2 ? -1 : cmp);
		cmp = (cmp == 0 && dot1 ? 1 : cmp);
	}
	return (cmp);
}

static int			sort_first(t_basic_list **lst, char *name, int type)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- SORT FIRST ----------");

	t_basic_list		*tmp;
	int					cmp;

	cmp = cmp_dupli((*lst)->data, name);
	if (cmp == 0)
		return (0);
	if (cmp > 0) // pkoi > 0 et pas juste different de 0 c est se priver d un cas non ?
	{
		tmp = (*lst);
		(*lst) = ft_basiclstnew(name, type);
		(*lst)->next = tmp;
		return (0);
	}
	else
	{
		if ((*lst)->next && cmp_dupli((*lst)->next->data, name) > 0)
		{
			tmp = (*lst)->next;
			(*lst)->next = ft_basiclstnew(name, type);
			(*lst)->next->next = tmp;
			return (0);
		}
	}
	return (1);
}

static int			insert_sort(t_basic_list **ite, char *name, int type)
{
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- INSERT SORT ----------");

	t_basic_list		*tmp;
	int					cmp;

	cmp = cmp_dupli((*ite)->next->data, name); // pkoi comparer name avec le next->data ?
	if (cmp == 0)
		return (0);
	else if (cmp > 0)
	{
		// insert le nouveau maillon construit avec name entre l'avant dernier et le dernier
		tmp = (*ite)->next;
		(*ite)->next = ft_basiclstnew(name, type);
		(*ite)->next->next = tmp;
		return (0);
	}
	else if (cmp < 0 && ((*ite)->next->next
				&& cmp_dupli((*ite)->next->next->data, name) > 0))
	{
		// insert le nouveau maillon construit avec name en dernier
		tmp = ft_basiclstnew(name, type);
		tmp->next = (*ite)->next->next;
		(*ite)->next->next = tmp;
		return (0);
	}
	return (1);
}
*/

void				sort_push(t_basic_list **lst, char *name, int type)
{
	/*
	if (DEBUG_COMPL == 1)
		ft_putendl("---------- SORT PUSH ----------");

	t_basic_list		*ite;

	ite = *lst;
	if (ite)
	{
		if (sort_first(lst, name, type) == 0)
			return ;
	}
	while (ite && ite->next) // tu t'arrete a l'avant dernier
	{
		if (insert_sort(&ite, name, type) == 0)
			return ;
		ite = ite->next;
	}
	*/
	ft_basiclstpushbck(lst, name, type);
}
