#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

# include "shell.h"

/*
** sh_bi_builtin
*/
int						is_builtin(char **cmd);
int						handle_builtin(char **cmd, char options[8][3][2]);
int						check_builtin(int fd, char **cmd, int pipefd_tab[2][2],
							t_lst_fd **lstfd);

/*
** sh_bi_local_var
*/
int						manage_local_var(char **cmd, int *i);

/*
** sh_bi_options
*/
int						check_opt(char **arg, int *i, char opt[3][2]);
int						cd_L(char **arg, char curr_opt, char opt[3][2]);
int						cd_P(char **arg, char curr_opt, char opt[3][2]);
int						env_i(char **arg, char curr_opt, char *bi);
int						export_p(char **arg, int i);

/*
** sh_bi_handle_env_modif
*/
char					*get_env(char *name, int local);
int						modif_env(char **arg, int len, int *i, char opt[3][2]);

/*
** sh_bi_cd
*/
int						bi_cd(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_echo
*/
int						bi_echo(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_env
*/
int						change_env(char *name, char *value, int local);
int						bi_env(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_exit
*/
int						del_stline(t_line **stline);
int						bi_exit(char **arg, t_duo **env, char opt[3][2]);
int						exit_pgm(int exit_code);

/*
** sh_bi_export
*/
int						bi_export(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_unset
*/
int						unset_check_env(char *value, char opt[3][2], int local);
int						bi_unset(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_unset
*/
int						unset_f(char **arg, char curr_opt, char *bi);
int						unset_v(char **arg, char curr_opt, char *bi);

/*
** sh_bi_setenv
*/
int						valid_env_name(char *str, char *bi);
int						bi_setenv(char **arg, t_duo **env, char opt[3][2]);

/*
** sh_bi_unsetenv
*/
int						del_env(t_duo **env, char *name, int local);
int						bi_unsetenv(char **arg, t_duo **env, char opt[3][2]);

#endif
