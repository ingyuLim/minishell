/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:51 by seunan            #+#    #+#             */
/*   Updated: 2023/10/05 16:15:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	atexit(leak);
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	init_vars(vars, envp);
	minishell(vars);
	free_vars(vars, argc, argv);
	return (g_status);
}

// todo
// 1. 히어독 시그널 처리
// 2. 리드라인 히스토리 (m1 mac이라 환경이 다를 수 있음)

void	minishell(t_vars *vars)
{
	char	*str;

	sigaction(SIGQUIT, NULL, &(vars->oact_quit)); // SIGQUIT을 oact_quit에 저장
	sigaction(SIGINT, NULL, &(vars->oact_int)); // SIGINT를 oact_int에 저장
	while (1)
	{
		vars->act.sa_handler = sigint_handler;
		sigaction(SIGINT, &(vars->act), NULL);
		vars->act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &(vars->act), NULL);
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (!quotes_check(str))
			continue ;
		add_history(str); // 엔터칠 때 히스토리에 저장되는 문제 있음
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
