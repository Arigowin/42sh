/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_termcaps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhaldi <nkhaldi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:42:40 by nkhaldi           #+#    #+#             */
/*   Updated: 2017/04/13 18:20:10 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TERMCAPS_H
# define SH_TERMCAPS_H

# include "shell.h"

/*
** sh_tc_termcap
*/
int						my_outc(int c);
int						init_term(int full_init);
int						reset_term();

/*
** sh_tc_insert_in_line
*/
int						fct_insert(char **s, int *pos, char c, t_line *stline);

/*
** sh_tc_delete_in_line
*/
int						fct_ctrl_d(char **s, int *pos, t_line *stline,
							t_history **history);
int						fct_backspace(char **s, int *pos, t_line *stline,
							t_history **history);
/*
** sh_tc_move_in_line
*/
int						fct_left(char **s, int *pos, t_line *l, t_history **h);
int						fct_right(char **s, int *pos, t_line *line,
							t_history **history);
int						fct_ctrl_left(char **s, int *pos, t_line *stline,
							t_history **history);
int						fct_ctrl_right(char **s, int *pos, t_line *stline,
							t_history **history);

/*
** sh_tc_move_up_down
*/
int						left_move_cdt(int pos, t_line *stline);
int						fct_down(char **s, int *pos, t_line *stline,
							t_history **hstory);
int						fct_up(char **s, int *p, t_line *l, t_history **h);

/*
** sh_tc_spec_key
*/
int						fct_end(char **s, int *pos, t_line *l, t_history **h);
int						fct_home(char **s, int *pos, t_line *l, t_history **h);
int						fct_del(char **s, int *pos, t_line *l, t_history **h);

/*
** sh_tc_history
*/
void					del_history(t_history **history);
void					add_history(t_history **h, char *line);
void					modif_history(t_history **hist, char *line, int mini);

/*
** sh_tc_move_in_history
*/
int						history_down(char **str, int *pos, t_line *stline,
							t_history **history);
int						history_up(char **s, int *p, t_line *l, t_history **h);

/*
** sh_tc_copy_paste
*/
int						fct_cut(char **s, int *pos, t_line *l, t_history **h);
int						fct_paste(char **s, int *pos, t_line *l, t_history **h);
int						fct_copy(char **s, int *pos, t_line *l, t_history **h);

/*
** sh_tc_add_del_in_copy
*/
int						str_addleft(char *tbl, char c);
int						str_delleft(char *tbl);
int						add_in_copy(char **s, int *p, t_line *stline, int dir);
int						del_in_copy(char **s, int *p, t_line *stline, int dir);

/*
** sh_tc_highlight
*/
int						hide_highlight(char **str, int *pos, t_line *stline,
							t_history **history);
int						fct_highlight(char **str, int *pos, t_line *stline,
							t_history **history);

/*
** sh_tc_completion
*/
char					*launch_select(t_basic_list *lst, char *word);
int						fct_tab(char **line, int *pos, t_line *stline,
							t_history **history);

/*
** sh_tc_completion_func
*/
char					*get_line(char *str, int pos);
int						parse_tilde(char **path);
int						split_path(char **word, char **path);
char					*compl_word(int file, char **word);

/*
** sh_tc_completion_func2
*/
int						complet_var(t_basic_list **lst, char **path,
							char **word);
int						init_getdircontent(t_basic_list **lst, char **path,
							char **word, int file);
int						display_or_not(int nb);

/*
** sh_tc_completion_get
*/
int						get_dircontent(int file, char *path, t_basic_list **l,
							char *word);
int						get_dircontent(int file, char *path, t_basic_list **l,
							char *word);
int						get_execinpath(int file, char *word, t_basic_list **l);
int						get_envlist(t_basic_list **lst, char **word);

/*
** sh_tc_completion_sort
*/
void					sort_push(t_basic_list **lst, char *name, int type);

#endif
