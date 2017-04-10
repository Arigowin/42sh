#ifndef SH_UTILITIES_H
# define SH_UTILITIES_H

# include "shell.h"

/*
** sh_signal
*/
int						check_signal(int loc);

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