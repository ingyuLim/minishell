/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:51 by seunan            #+#    #+#             */
/*   Updated: 2023/10/08 23:04:32 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	atexit(leak);
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	init_vars(vars, envp);
	signal(SIGCHLD, child_handler);
	minishell(vars);
	free_vars(vars, argc, argv);
	return (g_status);
}

// todo
// 1. 히어독 시그널 처리
// 2. 리드라인 히스토리 (m1 mac이라 환경이 다를 수 있음)

void	eof_exit(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("exit", 1);
		g_status = 0;
		exit(0);
	}
}

void	minishell(t_vars *vars)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("\033[0;36mminishell$\033[0m ");
		eof_exit(str);
		if (!quotes_check(str))
			continue ;
		if (*str != '\0')
			add_history(str);
		vars->lst = tokenize(str);
		if (vars->lst == NULL)
			;
		else if (syntax_check(vars->lst) == 0)
			g_status = 258;
		else if (vars->lst != NULL)
			execute_frame(vars);
		free_str_tok(str, &(vars->lst));
	}
}
