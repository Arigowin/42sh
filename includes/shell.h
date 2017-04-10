#ifndef SHELL_H
# define SHELL_H

			#include <stdio.h>
			#define DEBUG_COMPL 0
			# define ANTIBUG_LOCAL 0
			# define DEBUG_BI 0
			# define DEBUG 0
			# define ANTIBUG 0

# include "libft.h"
# include "sh_define.h"
# include "sh_key.h"
# include "sh_struct.h"
# include "sh_builtins.h"
# include "sh_read.h"
# include "sh_lexer_parser.h"
# include "sh_redirect.h"
# include "sh_termcaps.h"
# include "sh_utilities.h"

/*
** sh_check_tty
*/
int						checktty(t_line *stline);

/*
** sh_file_history
*/
int						load_history(t_history **history);
int						save_history(void);

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
** sh_init
*/
int						init_env(char **env, t_duo **env_cpy);
int						init_stline(t_line *stline);
int						reset_stline(t_line *stline);
int						init_pipefd(int pipefd_tab[2][2]);

/*
** sh_first_steps
*/
int						miniprt_reset_stline(t_line *stline);
int						mini_prt_handler(char **str, int *pos, t_line *stline);
int						display_prompt(void);
char					**cpy_env(char **env);
int						fill_path(t_duo **env);

#endif
