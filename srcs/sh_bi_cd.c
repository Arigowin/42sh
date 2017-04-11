#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"
#include "libft.h"
/*naima*/
static int			get_symlink(char **path)
{
	char				*tmp;
	char				*new_path;
	char				*pwd;

	tmp = NULL;
	new_path = NULL;
	pwd = get_env("PWD", ENV, TRUE);
	if (!ft_strcmp(*path, ".."))
	{
		ft_strdel(path);
		if ((*path = ft_strdup(srch_begining(pwd, '/'))) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL)); // utiliser la fct qui free pour pwd

	//	while (env_pwd[i--] != '/')
	//		len++;
	//	*path = ft_strsub(env_pwd, 0, (ft_strlen(env_pwd) - len - 1));
	}
	else if (pwd[ft_strlen(pwd) - 1] != '/')
	{
		if ((tmp = ft_strjoin(pwd, "/")) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));
		ft_strdel(&pwd);
		if ((new_path = ft_strjoin(tmp, *path)) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL)); // utiliser la fct qui free pour tmp
		ft_strdel(&tmp);
		ft_strdel(path);
		if ((*path = ft_strdup(new_path)) == NULL)
			return (sh_error(FALSE, 6, NULL, NULL));// utiliser la fct qui free pour new_path
		ft_strdel(&new_path);




//		tmp = ft_strjoin(pwd, "/");
//		ft_strdel(&pwd);
//		if ((pwd = ft_strdup(tmp)) == NULL)
//			return (sh_error(FALSE, 6, NULL, NULL));
//		ft_strdel(&tmp);
	//	new_path = ft_strjoin(pwd, *path);
	//	ft_strdel(&pwd);
	//	ft_strdel(path);
	//	if ((*path = ft_strdup(new_path)) == NULL)
	//		return (sh_error(FALSE, 6, NULL, NULL));
	//	ft_strdel(&new_path);
	}
	return (TRUE); // return ac free pour
}
//
//static int			switch_env_pwd(char *path, int is_symlink)
//{
//	char				*old_pwd;
//	char				*new_path;
//
//	old_pwd = get_env("PWD", FALSE);
//	if (!is_symlink)
//		new_path = getcwd(NULL, 0);
//	else
//		new_path = path;
//	change_env("OLDPWD", old_pwd, FALSE);
//	change_env("PWD", new_path, FALSE);
//	ft_strdel(&new_path);
//	ft_strdel(&old_pwd);
//	return (0);
//}
//
//static int			logical_change_dir(char **path, char last_opt, int *ret)
//{
//	struct stat			stat_buf;
//	int					stat_ret;
//
//	if (**path != '/')
//		getcwd_link_path(path, last_opt);
//	stat_ret = lstat(*path, &stat_buf);
//	if (chdir(*path) == ERROR)
//		manage_cd_errors(*path, stat_buf, stat_ret);
//	if (!stat_ret && S_ISLNK(stat_buf.st_mode))
//		switch_env_pwd(*path, TRUE);
//	else if (!stat_ret && !S_ISLNK(stat_buf.st_mode))
//		switch_env_pwd(*path, FALSE);
//	return (*ret = TRUE);
//}
//
//static int			physical_change_dir(char **path, int *ret)
//{
//	struct stat			stat_buf;
//	int					stat_ret;
//
//	stat_ret = stat(*path, &stat_buf);
//	if (!stat_ret && chdir(*path) == -1)
//		manage_cd_errors(*path, stat_buf, stat_ret);
//	ft_strdel(path);
//	if ((*path = ft_strdup(getcwd(NULL, 0))) == NULL)
//		return (sh_error(FALSE, 6, NULL, NULL));
//	switch_env_pwd(*path, TRUE);
//	return (*ret = TRUE);
//}
/*fin naima*/
static int			change_dir(char *path, char opt[3][2])
{
	if (DEBUG_BI == 0)
		printf("-----------------------------------CHANGE DIR --------------------------\n");

	struct stat			stat_buf;

	if (path[0] != '/' && (opt[0][1] == 1 || (opt[0][1] == 0 && opt[1][1] == 0)))
		get_symlink(&path);
	if (chdir(path) == -1)
	{
		printf("POUET!!!!!\n");
		if (stat(path, &stat_buf) == 0 && !S_ISDIR(stat_buf.st_mode))
			return (sh_error(FALSE, 16, path, NULL));
		else if ((access(path, F_OK)) == ERROR)
			return (sh_error(FALSE, 17, path, NULL));
		else
			return (sh_error(FALSE, 18, path, NULL));
	}
	return (TRUE);
}

static int			cd_home(char opt[3][2])
{
	if (DEBUG_BI == 0)
		printf("-----------------------------------CD HOME --------------------------\n");

	char				*path;
	int					ret;

	if ((path = get_env("HOME", ENV, TRUE)) == NULL)
		return (sh_error(FALSE, 13, NULL, NULL));
	ret = change_dir(path, opt);
	ft_strdel(&path);
	return (ret);
}

static int			handle_cd_arg(int *i, int *ret, char **arg, char opt[3][2])
{
	if (DEBUG_BI == 0)
		printf("----------------------------------- HANDLE CD ARG --------------------------\n");

	char				*tmp;

	tmp = get_env("OLDPWD", ENV, TRUE);
	while(arg[*i] && arg[*i][0] == '-' && arg[*i][1])
		(*i)++;
	while (arg[*i])
	{
		if (arg[*i] && arg[*i][0] == '-' && !arg[*i][1])
		{
			if (tmp)
			{
				*ret = change_dir(tmp, opt);
				return (TRUE);
			}
			return (sh_error(TRUE, 11, NULL, NULL));
		}
		else
		{
			*ret = change_dir(arg[*i], opt);
			return (TRUE);
		}
		(*i)++;
	}
	return (dblstr_duo_ret(TRUE, &tmp, NULL, NULL));
}

int					bi_cd(char **arg, char opt[3][2])
{
	if (DEBUG_BI == 0)
		printf("----------------------------------- BI CD --------------------------\n");

	char				*tmp;
	char				*path;
	int					i;
	int					ret;

	i = 1;
	ret = 0;
	tmp = NULL;
	path = NULL;
	if (check_opt(arg, &i, opt) == ERROR)
		return (FALSE);
//	printf("OPTION : i [[%d]] arg [[%s]] -L [[%d]] -P [[%d]] last opt? [[%d]]\n", i, arg[i], opt[0][1], opt[1][1], opt[2][1]);
	i = 1;
	if (!arg[i])
		ret = cd_home(opt);
	else if (handle_cd_arg(&i, &ret, arg, opt) == FALSE)
		return (FALSE);
	if (ret == TRUE)
	{
		tmp = get_env("PWD", ENV, TRUE);
		change_env("OLDPWD", tmp, ENV);
		path = getcwd(path, MAX_PATH);
		change_env("PWD", path, ENV);
	}
	return (dblstr_duo_ret(FALSE, &tmp, &path, NULL));
}
