#ifndef SH_REDIRECT_H
# define SH_REDIRECT_H

# include "shell.h"

/*
** fd_open
*/
int						fd_open(int	*fd, int reset_save, t_node *tree);

/*
** sh_rd_red
*/
int						fd_exist(int fd, char *filename);
int						heredoc_handler(t_line *l, t_node **t, t_history **h);
int						redirect(t_node *tree, t_lst_fd *lstfd);

/*
** sh_rd_manage_lstfd
*/
int						del_lstfd(t_lst_fd **lstfd);
t_lst_fd				*lstfd_new(int fd, char *filename);
int						close_lstfd(t_lst_fd **lstfd);
int						lstfd_pushfront(t_lst_fd **lstfd, int fd, char *name);
int						push_in_lstfd(t_node *tree, t_lst_fd **lstfd, int fd,
							int *fd_save);

/*
** sh_rd_redfd_handler
*/
int						check_file_name(char **filename, char *str);
int						reset_std_fd(void);
int						red_fd(int fd, t_node *tree, t_lst_fd **lstfd,
							t_types type);
t_lst_fd				*lstfd_insert(t_lst_fd **lstfd, t_lst_fd **tmpfd,
							int fd, char *filename);

/*
** sh_rd_heredoc
*/
int						check_end_heredoc(t_line *stline);
int						tree_trav_hrd(t_line *stline, t_node **tree,
							t_history **history);
int						manage_hrd_document(int bln, t_line *stline,
							t_node **tree, t_history **history);

/*
** sh_end_pipe_quote
*/
int						check_end_pipe(char **str, int *pos);
int						check_nb_quote(char c, int back, int *quote, int fill);
int						quote_is_close(char **str);
int						handle_quote(int key, char **str, int *pos,
							t_line *stline);

/*
** sh_pipe
*/
int						pfd_handler(int pipefd_tab[2][2]);
int						pfd_close(int pipefd_tab[2][2]);
int						pipe_function(int pipefd_tab[2][2], t_node *tree,
							t_lst_fd **lstfd);

#endif
