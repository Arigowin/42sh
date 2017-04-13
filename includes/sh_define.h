/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:18:36 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:18:36 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DEFINE_H
# define SH_DEFINE_H

# define HISTORY_FILE_NAME "/.42sh_history"

# define CONTINUE 3
# define BREAK 2
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define NO_RED_ARG -2
# define SYS_CALL_FAIL -3
# define NO_PRINT -4

# define IGN " \t\n"
# define SEP "|&;>< \t\n\0"
# define SPECIAL "|&><;"
# define SPECIAL2 "|><;"
# define LWAKA "><|&"
# define WAKA "><"

# define BUFF_SIZE 1024
# define MAX_PATH 1024

# define QUOTE 39
# define DQUOTE 34

# define PRT_LEN 2

# define COLOR "\033[0;30;46m"
# define RESET_COLOR "\033[0m"

#endif
