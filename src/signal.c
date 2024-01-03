/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:36 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:23:49 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

void	child_handler(int signo)
{
	(void)signo;
	if (g_status == 2 || g_status == 3)
		g_status += 128;
	else if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
}

void	sigint_handler(int signo)
{
	(void)signo;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	// rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	heredoc_handler(int signo)
{
	(void) signo;
	g_status = 1;
	ft_putchar_fd('\n', 1);
	close(0);
}

void	sigint_handler_exec(int signum)
{
	(void)signum;
	g_status = 130;
	ft_putstr_fd("\n", 1);
}

void	sigquit_handler_exec(int signum)
{
	(void)signum;
	g_status = 131;
	ft_putstr_fd("Quit: 3\n", 1);
}
