/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:36 by seunan            #+#    #+#             */
/*   Updated: 2023/10/04 00:59:18 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_action(t_vars *vars)
{
	vars->act.sa_handler = sigint_handler;
	sigaction(SIGINT, NULL, &(vars->oact_int));
	sigaction(SIGINT, &(vars->act), NULL);
	vars->act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, NULL, &(vars->oact_quit));
	sigaction(SIGQUIT, &(vars->act), NULL);
}

void	sigint_handler(int signo)
{
	(void) signo;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_exec(int signum)
{
	(void) signum;
	g_status = 130 << 8;
	ft_putstr_fd("\n", 1);
}
