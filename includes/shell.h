/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:18:45 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:18:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "sh_define.h"
# include "sh_key.h"
# include "sh_struct.h"
# include "sh_termcaps.h"
# include "sh_builtins.h"
# include "sh_read.h"
# include "sh_lexer_parser.h"
# include "sh_redirect.h"
# include "sh_utilities.h"

/*
** sh_main.c
*/
t_duo					*savior_env(t_duo *env, int code);

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
