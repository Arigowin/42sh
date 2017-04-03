/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:37:29 by avacher           #+#    #+#             */
/*   Updated: 2016/04/12 18:37:29 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
#include "libft.h"

# define DEBUG_FT_SELECT 1

# define TRUE 1
# define FALSE 0
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define SPACE 32
# define DELETE 2117294875
# define BACKSPACE 127
# define RETURN 10
# define ESCAPE 27

typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct			s_cduo
{
	char				*name;
	int					first;
	int					select;
	int					cursor;
	int					col_nb;
	int					no_elt;
	int					first_disp;
	struct s_cduo		*prev;
	struct s_cduo		*next;
}						t_cduo;

typedef struct			s_glst
{
	t_cduo				*lst_param;
	int					fd;
	int					max_len;
	int					nb_elt;
	int					nb_col;
	int					col_size;
}						t_glst;

int						cduo_pushback(t_cduo **lst_param, char *name, int no);
void					free_lst_param();
int						ft_select(t_basic_list *lst);

/*
** first_steps.c
*/
int						ft_putchr(int c);
void					clr_screen(void);
int						fill_list(t_cduo **lst_param, t_basic_list *lst);
char					**select_read(void);

/*
** init.c
*/
int						enable_keyboard(void);
int						hide_cursor(void);
int						termcap_init(void);

/*
** reset.c
*/
int						disable_keyboard(void);
int						display_cursor(void);
void					termcap_reset(void);

/*
** display.c
*/
int						get_col_size(void);
int						manage_win_size(void);
int						print_return(char ***ret);

/*
** display_select.c
*/
int						manage_columns(void);

/*
** moves.c
*/
int						down_arrow(int i);
int						up_arrow();

/*
** actions.c
*/
char					**enter_key();
char					**esc_key(void);
int						suppr_key();

/*
** manage_struct.c
*/
t_winsize				*fct_size();
int						get_s_win();
t_glst					*get_stuff();
t_termios				*get_term();

/*
** signal
*/
void					sig_continue(int sig);
void					manage_signal();

#endif

/*
**# define RIGHT_ARROW 4414235
**# define LEFT_ARROW 4479771
*/
