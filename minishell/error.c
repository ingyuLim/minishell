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

void	exit_with_err(char *err, char *cmd)
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
	exit(EXIT_FAILURE);
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
