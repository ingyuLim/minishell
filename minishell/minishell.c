#include "minishell.h"

void	minishell(t_vars *vars)
{
	char	*str;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(str);
		if (replace_and_check(&str, vars) == 0)
			continue ;
		vars->lst = tokenize(str);
		if (syntax_check(vars->lst) == 1)
		{
			free_str_tok(str, &(vars->lst));
			continue ;
		}
		print_tokens(vars->lst);
		execute(vars);
		free_str_tok(str, &(vars->lst));
	}
}
