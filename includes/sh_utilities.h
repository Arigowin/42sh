#ifndef SH_UTILITIES_H
# define SH_UTILITIES_H

# include "libft.h"

/*
** sh_signal
*/
int						check_signal(int loc);

/*
** sh_savior
*/
t_duo					*savior_env(t_duo *env, int code);
t_line					*savior_stline(t_line *stline, int code);
char					*savior_tty(char *tty, int code);
t_node					*savior_tree(t_node *tree, int code);
t_history				**savior_history(t_history **history, int code);
int						savior_pid(int fct_pid, int code);

/*
** sh_error
*/
int						sh_error(int ret, int index, char *err, char *bi);

/*
** free_return
*/
int						str_dbltbl_ret(int ret, char **str, char ***tbl1,
							char ***tbl2);
int						telist_ret(int ret, t_e_list **lst1, char **str1,
							char **str2);
int						lstfd_node_ret(int ret, t_node **node, t_lst_fd **lstfd,
							char **str2);
int						dblstr_duo_ret(int ret, char **str1, char **str2,
							t_duo **duo1);
int						dblstr_hist_ret(int ret, char **str1, char **str2,
							t_history **hist);

/*
** free_return_error
*/
int						error_clear_node(int ret, int index, char *err,
							t_node **to_free);
int						error_clear_str(int ret, int index, char *err,
							char **to_free);
int						error_clear_dblstr(int ret, int index, char **to_free,
							char **to_free_bis);
int						error_clear_tab(int ret, int index, char *err,
							char ***to_free);
void					exit_clear_stline(int ret, t_line **stline);

#endif
