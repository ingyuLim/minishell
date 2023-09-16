#include "minishell.h"

int	main(char *envp[])
{
	atexit(leak);
	t_list	*lst;
	char	*str;

	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		lst = tokenize(str);
		if (syntax_check(lst) == 1)
		{
			free_strtok(str, &lst);
			continue ;
		}
		add_history(str);
		// print_tokens(lst);
		execute(lst, envp);
		free_strtok(str, &lst);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?

// "g"r"epadasdasfasd"
