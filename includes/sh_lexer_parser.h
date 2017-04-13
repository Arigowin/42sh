/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:18:38 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:18:38 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_PARSER_H
# define SH_LEXER_PARSER_H

# include "shell.h"

/*
** sh_t_e_list_handler
*/
int						expr_del(t_e_list **new);
t_e_list				*expr_new(char *content, int hrd);
int						expr_pushbk(t_e_list **l_expr, char *data_tmp, int hrd);

/*
** sh_lp_finite_state_automaton
*/
int						finite_state_automaton(int *hrd, char **read_buff,
							t_e_list **l_expr, char **data_tmp);
/*
** sh_lp_tokenizer
*/
int						concat(char **dest, char *s1, char *s2);
int						token_sep(int *hrd, char **read_buff, char **data_tmp,
							t_e_list **l_expr);
int						tokenizer(int *hrd, char *read_buff, t_e_list **l_expr);

/*
** sh_lp_tokenizer_spec
*/
int						token_backslash(t_states state, char **read_buff,
							char **data_tmp);
int						token_dollar(char **read_buff, char **data_tmp, int rm);
int						token_tilde(char **buff, char **data_tmp, int *bln);

/*
** sh_lp_lexer
*/
int						lexer(t_e_list **l_expr);

/*
** sh_lp_lexer_waka
*/
int						waka_lexer(t_e_list **l_expr);

/*
** sh_create_tree
*/
t_node					*create_node(t_types type);

/*
** sh_free_tree
*/
int						clear_node(t_node **node);
int						del_tree(t_node **tree);

/*
** sh_lp_parser
*/
int						parse_error(char *data);
int						parser(int *nb_hrd, t_e_list **l_expr, t_node **tree);

/*
** sh_lp_parser_additional_items
*/
int						check_red(int *nb_hrd, t_e_list **l_expr, t_node **t);
int						check_next(int *nb_hrd, t_e_list **l_expr, t_node **t,
							t_node **r_n);

/*
** sh_lp_parser_useful_fct
*/
int						fill_leaf(t_e_list **l_expr, t_node **node);
t_types					fill_red_type(char *data, int *nb_hrd);
int						parser_ret_fct(int ret, t_node **tree, t_node **node,
							t_node **to_free);
int						move_in_list(t_e_list **l_expr);

/*
** sh_lp_parser_additional_items
*/
int						parser_ret_fct(int ret, t_node **tree, t_node **node,
						t_node **to_free);

#endif
