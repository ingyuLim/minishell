#include "minishell.h"

void	sigint_handler(int signo)
{
	(void) signo;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signo)
{
	(void) signo;
	rl_on_new_line();
	rl_redisplay();
}
