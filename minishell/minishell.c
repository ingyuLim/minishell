#include "minishell.h"

void	minishell(t_vars *vars)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		str = replace_env_vars(str, vars->env);	// 환경변수 치환
		vars->lst = tokenize(str);				// 토큰화
		if (vars->lst == NULL)
		{
			free(str);
			error("It doesn't match");
			continue ;
		}
		if (syntax_check(vars->lst) == 1)		// 문법 체크
		{
			free_str_tok(str, &(vars->lst));
			continue ;
		}
		add_history(str);
		print_tokens(vars->lst);
		execute(vars);
		free_str_tok(str, &(vars->lst));
	}
}
