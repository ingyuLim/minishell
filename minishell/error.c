#include "minishell.h"

void	error(char *err)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(err);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
}

void	exit_with_msg(char *msg)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_with_err(char *err)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(err);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
