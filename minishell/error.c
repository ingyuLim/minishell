/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:53 by seunan            #+#    #+#             */
/*   Updated: 2023/09/30 00:32:06 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *err, char *cmd)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror(err);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
}

void	exit_with_err(char *err, char *cmd, int status)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror(err);
	ft_putstr_fd("\n\033[0m", STDERR_FILENO);
	exit(status);
}

void	error_msg(char *msg, char *cmd, char *arg)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n\033[0m", STDERR_FILENO);
}

void	exit_with_msg(char *msg, char *cmd, char *arg)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
