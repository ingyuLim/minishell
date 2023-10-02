/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:51 by seunan            #+#    #+#             */
/*   Updated: 2023/10/02 22:45:18 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	// atexit(leak);
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	init_vars(vars, envp);
	minishell(vars);
	free_vars(vars, argc, argv);
	return (g_status);
}

void	minishell(t_vars *vars)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		add_history(str);
		if (!quotes_check(str))
			continue ;
		vars->lst = tokenize(str);
		if (vars->lst == NULL)
			;
		else if (syntax_check(vars->lst) == 0)
			g_status = 258;
		else
			execute_frame(vars);
		free_str_tok(str, &(vars->lst));
	}
}
