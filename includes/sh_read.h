#ifndef SH_READ_H
# define SH_READ_H

# include "shell.h"

/*
** sh_fct_read
*/
int						tree_traversal_verif(t_node *tree);
int						check_after_read(t_line *stline, t_history **history);
int						ctrl_c_hrd(t_line *stline, int prt);
int						fct_read(int hrd, t_line *line, t_history **history);

/*
** sh_father_n_son
*/
int						handle_fork(int pipefd_tab[2][2], t_node *tree,
							t_lst_fd **lstfd, char **cmd);

/*
** sh_cmd_line_assemble
*/
int						ft_is_dir(char *path);
int						null_input(int fd);
int						check_fct(int fd, char **cmd);

/*
** sh_event
*/
int						quote_is_close(char **str);
int						event(int key, t_line *stline, t_history **history);

/*
** sh_tree_traversal
*/
int						tree_traversal(t_node *tree, t_lst_fd **lstfd,
							int pipefd[2][2]);

/*
** sh_cmd
*/
int						manage_cmd(int pipefd_tab[2][2], t_node *tree,
							t_lst_fd **lstfd);

#endif
