#include "shell.h"
#include "libft.h"

int					token_backslash(t_states state, char **r_buff,
					char **data_tmp)
{
	(void)state;
	if (**r_buff == '\\' && (*(*r_buff + 1)) && (*(*r_buff + 1)) == '\n')
		(*r_buff) += 1;
	else
	{
		if (state == IN_DQUOTE && **r_buff && **r_buff == '\\'
		&& (*(*r_buff + 1)) && (*(*r_buff + 1)) != '$'
		&& (*(*r_buff + 1)) != '`' && (*(*r_buff + 1)) != '"'
		&& (*(*r_buff + 1)) != '\\' && (*(*r_buff + 1)) != '\n')
			add_in_tbl(data_tmp, **r_buff);
		(*r_buff)++;
		add_in_tbl(data_tmp, **r_buff);
	}
	return (TRUE);
}

int					token_dollar(char **read_buff, char **data_tmp)
{
	char				*env_name;
	char				*env_val;
	char				*tmp;

	tmp = NULL;
	if ((env_name = ft_strnew(ft_strlen((*read_buff)++))) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	while ((ft_strchr(SEP, **read_buff) == NULL && ft_strchr("/", **read_buff)
	== NULL) && **read_buff != QUOTE && **read_buff != DQUOTE)
		add_in_tbl(&env_name, (*((*read_buff)++)));
	(*read_buff)--;
	if (ft_strcmp(env_name, "$") == 0)
		env_val = ft_itoa(getpid());
	else if ((env_val = get_env(env_name, TRUE)) == NULL && (env_val = get_env(env_name, FALSE)) == NULL)
		return (dblstr_duo_ret(FALSE, &env_name, NULL, NULL));
	ft_strdel(&env_name);
	if (*data_tmp && (tmp = ft_strdup(*data_tmp)) == NULL)
		return (error_clear_str(FALSE, 6, NULL, &env_val));
	ft_strdel(data_tmp);
	if ((*data_tmp = ft_strnew(ft_strlen(tmp) + ft_strlen(env_val)
	+ ft_strlen(*read_buff))) == NULL)
		return (error_clear_dblstr(FALSE, 6, &tmp, &env_val));
	concat(data_tmp, tmp, env_val);
	return (dblstr_duo_ret(TRUE, &env_val, &tmp, NULL));
}

int					token_tilde(char **read_buff, char **data_tmp, int *bln)
{
	char				*val;
	char				*tmp;

	tmp = NULL;
	/*
	if ((!(val = get_env("HOME", FALSE)) && !(val = get_env("HOME", FALSE))) || !ft_strchr(SEP, *(*read_buff - 1))
			|| (*(*read_buff + 1) && !ft_strchr(SEP, *(*read_buff + 1))
				&& *(*read_buff + 1) != '/'))
	*/
	// 1er get_env doit etre a false au lieu de true
	if ((!(val = get_env("HOME", FALSE)) && !(val = get_env("HOME", FALSE)))
	|| !ft_strchr(SEP, *(*read_buff - 1))
	|| (*(*read_buff + 1) && !ft_strchr(SEP, *(*read_buff + 1))
	&& *(*read_buff + 1) != '/'))
		return (dblstr_duo_ret(FALSE, &val, NULL, NULL));
	if (*data_tmp && (tmp = ft_strdup(*data_tmp)) == NULL)
		return (error_clear_str(FALSE, 6, NULL, &val));
	ft_strdel(data_tmp);
	if ((*data_tmp = ft_strnew(ft_strlen(tmp) + ft_strlen(val)
					+ ft_strlen((*read_buff)++))) == NULL)
	{
		ft_strdel(&val);
		ft_strdel(&tmp);
		return (sh_error(FALSE, 6, NULL, NULL));
	}
	concat(data_tmp, tmp, val);
	*bln = TRUE;
	return (dblstr_duo_ret(TRUE, &val, &tmp, NULL));
}
