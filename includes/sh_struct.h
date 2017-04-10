#ifndef SH_STRUCT_H
# define SH_STRUCT_H

# include <sys/ioctl.h>

typedef enum			e_types
{
	NONE,
	EXP,
	SEMI,
	PIPE,
	CMD,
	CMD_ARG,
	RED,
	RED_FD,
	RED_ARG,
	HRD_QUOTE,
	RRED,
	LRED,
	DRRED,
	DLRED,
	RWRED,
	DLRED_DOC,
	LOGIC_AND,
	LOGIC_OR,
	AMP
}						t_types;

typedef enum			e_states
{
	STANDARD,
	IN_QUOTE,
	IN_DQUOTE
}						t_states;

typedef struct			s_e_list
{
	char				*data;
	t_types				type;
	int					hrd_quote;
	struct s_e_list		*next;
}						t_e_list;

typedef struct			s_node
{
	int					quote;
	char				*data;
	t_types				type;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct			s_copy
{
	char				*cpy;
	char				*bkup;
	int					pos;
	int					start;
}						t_copy;

typedef struct			s_heredoc
{
	int					nb;
	int					pos;
	int					ctrl_d;
	struct s_node		*deli;
	char				*line;
	char				*ptr;
}						t_heredoc;

typedef struct			s_line
{
	int					pos;
	int					curs_x;
	int					curs_y;
	int					mini_prt;
	int					quote;
	int					ctrl_c;
	char				*line;
	char				*curr_hist;
	struct winsize		win;
	struct s_copy		copy;
	struct s_heredoc	hrd;
}						t_line;

typedef struct			s_history
{
	char				*line;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_key_fct
{
	int					key;
	int					(*fct)(char **str, int *pos, t_line *stline,
							t_history **history);
}						t_key_fct;

typedef struct			s_lst_fd
{
	int					fd;
	char				*filename;
	struct s_lst_fd		*next;
}						t_lst_fd;

#endif
