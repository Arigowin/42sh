/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:48:41 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:12:29 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_duo				*savior_env(t_duo *env, int code_env)
{
	static t_duo		*save_env = NULL;

	if ((save_env == NULL && env) || code_env == TRUE)
		save_env = env;
	return (save_env);
}

int					main(void)
{
	extern char			**environ;
	t_duo				*env_cpy;
	t_line				stline;
	t_history			*history;

	history = NULL;
	if (init_env(environ, &env_cpy) == ERROR)
		return (ERROR);
	init_stline(&stline);
	checktty(&stline);
	load_history(&history);
	init_term(TRUE);
	while (TRUE)
	{
		reset_stline(&stline);
		check_signal(1);
		display_prompt();
		if (fct_read(FALSE, &stline, &history) == ERROR)
			break ;
	}
	reset_term();
	return (dblstr_duo_ret(0, &(stline.line), &(stline.hrd).line, &env_cpy));
}
