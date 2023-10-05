/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:36 by seunan            #+#    #+#             */
/*   Updated: 2023/10/05 16:55:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child_handler(int signo)
{
	(void) signo;
    waitpid(-1, &g_status, WNOHANG);
}

void	sigint_handler(int signo)
{
	(void) signo;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	sigint_handler_exec(int signum)
{
	(void) signum;
	g_status = 130 << 8;
	ft_putstr_fd("\n", 1);
}

void	sigquit_handler(int signum)
{
	(void) signum;
	g_status = 131 << 8;
	ft_putstr_fd("Quit: 3\n", 1);
}
