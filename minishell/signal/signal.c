/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:55:43 by seunan            #+#    #+#             */
/*   Updated: 2023/10/06 16:32:33 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_origin(t_vars *vars)
{
	signal(SIGCHLD, child_handler);
	sigaction(SIGQUIT, NULL, &(vars->oact_quit));
	sigaction(SIGINT, NULL, &(vars->oact_int));
}

void	signal_handler(t_vars *vars)
{
	vars->act.sa_handler = sigint_handler;
	sigaction(SIGINT, &(vars->act), NULL);
	vars->act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &(vars->act), NULL);
}

void	signal_handler_exec(t_vars *vars)
{
	vars->act.sa_handler = sigint_handler_exec;
	sigaction(SIGINT, &(vars->act), NULL);
	vars->act.sa_handler = sigquit_handler_exec;
	sigaction(SIGQUIT, &(vars->act), NULL);
}
