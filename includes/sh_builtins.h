#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

# include <sys/stat.h>
# include "shell.h"

/*
** sh_bi_builtin
*/
int						is_builtin(char **cmd);
int						handle_builtin(char **cmd, char options[8][3][2]);
int						check_builtin(int fd, char **cmd, t_lst_fd **lstfd);

/*
** sh_bi_local_var
*/
int						manage_local_var(char **cmd, int *i);

/*
** sh_bi_options
*/
int						check_opt(char **arg, int *i, char opt[3][2]);

/*
** sh_bi_handle_env_modif
*/
int						change_env(char *name, char *value, t_env type);
int						modif_env(char **arg, int len, int *i, char opt[3][2]);
char					*get_env(char *name, t_env type, int all_env);

/*
** sh_bi_cd
*/
int						bi_cd(char **arg, char opt[3][2]);

/*
** sh_bi_cd_fct
*/
int						manage_cd_errors(char *p, struct stat s, int stat_r);
int						switch_env_pwd(char *path, int is_symlink);
int						logical_change_dir(char **path, char l_opt);

/*
** sh_bi_echo
*/
int						bi_echo(char **arg, char opt[3][2]);

/*
** sh_bi_env
*/
int						print_env(int eol);
int						format_env(char *arg);
int						del_tmp_env(int opt_i);
int						bi_env(char **arg, char opt[3][2]);

/*
** sh_bi_exit
*/
int						del_stline(t_line **stline);
int						bi_exit(char **arg, char opt[3][2]);
int						exit_pgm(int exit_code);

/*
** sh_bi_export
*/
int						bi_export(char **arg, char opt[3][2]);

/*
** sh_bi_unset
*/
int						bi_unset(char **arg, char opt[3][2]);

/*
** sh_bi_setenv
*/
int						valid_env_name(char *str, char *bi);
int						bi_setenv(char **arg, char opt[3][2]);

/*
** sh_bi_unsetenv
*/
int						del_env(char *name);
int						bi_unsetenv(char **arg, char opt[3][2]);

#endif
