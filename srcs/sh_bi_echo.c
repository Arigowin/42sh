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
	buff = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '0')
		{
			while (str[++i] && ft_isdigit(str[i]) == 1)
				add_in_tbl(&buff, str[i]);
			ft_putchar(ft_atoi_base(buff, 8));
			ft_bzero(buff, ft_strlen(buff));
			i--;
		}
		else if (str[i] == '\\' && str[i + 1] == 'c')
			return (2);
		else
			parse_str_bis(str, &i);
		i++;
	}
	return (TRUE);
}

int					echo_n(char **arg, char curr_opt, char *bi)
{
	int				i;

	(void)bi;
	i = 1;
	if (curr_opt != 'n')
		return (FALSE);
	while (arg[i][0] == '-')
		i++;
	while (arg[i])
	{
		if (parse_str(arg[i]) == 2)
			return (TRUE);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (TRUE);
}

int					bi_echo(char **arg, t_duo **env, const char *opt)
{
	int i;

	i = 1;
	(void)env;
	if (check_opt(arg, &i, opt) == TRUE)
		return (TRUE);
	if (tbl_len(arg) > 1)
	{
		while (arg && arg[i])
		{
			ft_putstr_visible(arg[i]);
			if (arg[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	ft_putchar('\n');
	return (TRUE);
}
