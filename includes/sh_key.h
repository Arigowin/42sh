/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_key.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:18:37 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:18:38 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_KEY_H
# define SH_KEY_H

# define LEFT 4479771
# define RIGHT 4414235
# define UP 4283163
# define DOWN 4348699
# define BACKSPACE 127
# define TAB 9
# define RETURN 10
# define CTRL_D 4
# define DEL 2117294875

# include "shell.h"

# if defined(__unix__)

/*
** LINUX CTRL + [q|w]
*/
#  define CTRL_UP 28955
#  define CTRL_DOWN 30491

/*
** LINUX ALT + [h|v|c|x]
*/
#  define HIGHLIGHT 26651
#  define PASTE 30235
#  define COPY 25371
#  define CUT 30747

/*
** LINUX CTRL + [a|e]
*/
#  define CTRL_LEFT 1
#  define CTRL_RIGHT 5

/*
** LINUX
*/
#  define HOME 2117163803
#  define END 2117360411

# elif defined(__APPLE__)

/*
** MAC
*/
#  define CTRL_UP 16693
#  define CTRL_DOWN 16949

/*
** MAC OPT + [h|v|c|x]
*/
#  define HIGHLIGHT 39371
#  define PASTE 10127586
#  define COPY 42947
#  define CUT 8948194

/*
** MAC
*/
#  define CTRL_LEFT 17461
#  define CTRL_RIGHT 17205

/*
** MAC
*/
#  define HOME 4741915
#  define END 4610843

# endif

#endif
