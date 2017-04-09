#include <term.h>
#include "shell.h"
#include "libft.h"

int					my_outc(int c)
{
	ft_putchar(c);
	return (0);
}

static int			start_init_term(void)
{
	char				*term_name;

	term_name = NULL;
	if ((term_name = get_env("TERM", BOTH)) == NULL)
		term_name = "xterm";
	tgetent(NULL, term_name);
	ft_strdel(&term_name);
	return (TRUE);
}

int					init_term(int full_init)
{
	struct termios		term;

	if (ttyname(0) == NULL)
		return (FALSE);
	if (full_init == TRUE)
	{
		if (start_init_term() == ERROR)
			return (ERROR);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	return (TRUE);
}

int					reset_term(void)
{
	struct termios		term;

	if (ttyname(0) == NULL)
		return (FALSE);
	tputs(tgetstr("ve", NULL), 1, my_outc);
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	return (TRUE);
}
