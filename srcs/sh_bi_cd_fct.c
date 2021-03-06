/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bi_cd_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:52 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 17:37:27 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "shell.h"
#include "libft.h"

static int			absolute_link_path_builder(char **path, char **env_pwd)
{
	char				*new_path;
	char				*tmp_path;

	new_path = NULL;
	if (ft_strcmp(*env_pwd, "/") != 0)
	{
		tmp_path = ft_strjoin(*env_pwd, "/");
		ft_strdel(env_pwd);
		if ((*env_pwd = ft_strdup(tmp_path)) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		ft_strdel(&tmp_path);
	}
	new_path = ft_strjoin(*env_pwd, *path);
	ft_strdel(env_pwd);
	ft_strdel(path);
	if ((*path = ft_strdup(new_path)) == NULL)
		return (sh_error(FALSE, 6, NULL, NULL));
	ft_strdel(&new_path);
	return (TRUE);
}

static int			getcwd_link_path(char **path, char last_opt)
{
	char				*env_pwd;
	int					i;
	int					len;

	if ((env_pwd = get_env("PWD", ENV, TRUE)) == NULL)
		env_pwd = getcwd(NULL, 0);
	i = ft_strlen(env_pwd) - 1;
	len = 0;
	if (ft_strcmp(*path, ".") == 0)
	{
		if ((*path = ft_strdup(env_pwd)) == NULL)
			return (error_clear_str(FALSE, 6, NULL, &env_pwd));
	}
	else if (!ft_strcmp(*path, "..") && (!last_opt || last_opt == 'L') && i)
	{
		ft_strdel(path);
		while (env_pwd[i--] != '/')
			len++;
		len -= ((ft_strlen(env_pwd) - len - 1) == 0 ? 1 : 0);
		*path = ft_strsub(env_pwd, 0, (ft_strlen(env_pwd) - len - 1));
	}
	else
		absolute_link_path_builder(path, &env_pwd);
	ft_strdel(&env_pwd);
	return (TRUE);
}

int					manage_cd_errors(char *pth, struct stat stat_bf, int stat_r)
{
	if (!stat_r && !S_ISDIR(stat_bf.st_mode))
		return (sh_error(FALSE, 16, pth, NULL));
	else if ((access(pth, F_OK)) == ERROR)
		return (sh_error(FALSE, 17, pth, NULL));
	else
		return (sh_error(FALSE, 18, pth, NULL));
}

int					switch_env_pwd(char *path, int is_symlink)
{
	char				*old_pwd;
	char				*new_path;

	old_pwd = get_env("PWD", ENV, TRUE);
	if (!is_symlink)
		new_path = getcwd(NULL, 0);
	else
	{
		if ((new_path = ft_strdup(path)) == NULL)
			return (error_clear_str(FALSE, 6, NULL, &old_pwd));
	}
	change_env("OLDPWD", old_pwd, ENV);
	change_env("PWD", new_path, ENV);
	ft_strdel(&new_path);
	ft_strdel(&old_pwd);
	return (TRUE);
}

int					logical_change_dir(char **path, char last_opt)
{
	struct stat			stat_buf;
	int					stat_ret;

	if (**path != '/')
		getcwd_link_path(path, last_opt);
	stat_ret = lstat(*path, &stat_buf);
	if (chdir(*path) == ERROR)
		return (manage_cd_errors(*path, stat_buf, stat_ret));
	if (!stat_ret && S_ISLNK(stat_buf.st_mode))
		switch_env_pwd(*path, TRUE);
	else if (!stat_ret && !S_ISLNK(stat_buf.st_mode))
		switch_env_pwd(*path, FALSE);
	return (TRUE);
}
