#include "shell.h"
#include "libft.h"

void				put_add(char c, int *i)
{
	ft_putchar(c);
	(*i)++;
}

void				parse_str_bis(char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1] == 'a')
		put_add('\a', i);
	else if (str[*i] == '\\' && str[*i + 1] == 'b')
		put_add(8, i);
	else if (str[*i] == '\\' && str[*i + 1] == 'f')
		put_add('\f', i);
	else if (str[*i] == '\\' && str[*i + 1] == 'n')
		put_add('\n', i);
	else if (str[*i] == '\\' && str[*i + 1] == 'r')
		put_add('\r', i);
	else if (str[*i] == '\\' && str[*i + 1] == 't')
		put_add('\t', i);
	else if (str[*i] == '\\' && str[*i + 1] == 'v')
		put_add('\v', i);
	else if (str[*i] == '\\' && str[*i + 1] == '\\')
		put_add('\\', i);
	else
		ft_putchar(str[*i]);
}

int					parse_str(char *str)
{
	int					i;
	char				*buff;

	i = 0;
	if ((buff = ft_strnew(ft_strlen(str))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '0')
		{
			while (str[++i] && ft_isdigit(str[i]) == 1 && ft_strlen(buff) < 4)
				add_in_tbl(&buff, str[i]);
			ft_putchar(ft_atoi_base(buff, 8));
			ft_bzero(buff, ft_strlen(buff));
			i--;
		}
		else if (str[i] == '\\' && str[i + 1] == 'c')
			return (str_dbltbl_ret(FALSE, &buff, NULL, NULL));
		else
			parse_str_bis(str, &i);
		i++;
	}
	ft_strdel(&buff);
	return (TRUE);
}

int					bi_echo(char **arg, char opt[3][2])
{
	int					i;
	int					ret;

	i = 1;
	if ((ret = check_opt(arg, &i, opt)) == ERROR)
		return (FALSE);
	i = (ret == TRUE ? i : 1);
	ret = -1;
	if (tbl_len(arg) > 1)
	{
		while (arg && arg[i])
		{
			if (opt[1][1] == 1 && (ret = parse_str(arg[i])) == FALSE)
				break ;
			else if (opt[1][1] == 0)
				ft_putstr_visible(arg[i]);
			if (arg[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	if (opt[0][1] == 0 && ret != FALSE)
		ft_putchar('\n');
	return (TRUE);
}
