#include "shell.h"
#include "libft.h"

int					bi_unset(char **arg, t_duo **env, const char *opt)
{
(void)arg;
(void)env;
(void)opt;
	bi_unsetenv(arg, env, opt);
	return (TRUE);
}
