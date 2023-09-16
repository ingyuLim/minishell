#include "minishell.h"

void	exit_with_msg(char *msg)
{
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
