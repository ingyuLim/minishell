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
		add_history(str);
		if (replace_and_check(&str, vars) == 0)
			continue ;
		vars->lst = tokenize(str);				// 토큰화
		print_tokens(vars->lst);
		if (syntax_check(vars->lst) == 1)		// 문법 체크
		{
			free_str_tok(str, &(vars->lst));
			continue ;
		}
		print_tokens(vars->lst);
		execute(vars);
		free_str_tok(str, &(vars->lst));
	}
}

int	replace_and_check(char **str, t_vars *vars)
{
	*str = replace_env_vars(*str, vars->env);	// 환경변수 치환
	if (is_valid_quotes(*str) == 0)			// 따옴표 검사
	{
		free(*str);
		error_msg("Invalid quotes");
		return (0);
	}
	return (1);
}

int	is_valid_quotes(char *str)
{
	int	i;
	int	sin;
	int	dou;

	i = 0;
	sin = 0;
	dou = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dou % 2 == 0)
			sin++;
		else if (str[i] == '\"' && sin % 2 == 0)
			dou++;
		i++;
	}
	if (sin % 2 == 0 && dou % 2 == 0)
		return (1);
	return (0);
}
