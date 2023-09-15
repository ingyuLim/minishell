#include "minishell.h"

void	leak(void)
{
	system("leaks minishell > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}

void	print(t_list *lst)
{
	int	cnt = 0;

	printf("\033[1;37m");
	while (lst != NULL)
	{
		printf("%d: %s\n", cnt, lst->token);
		lst = lst->next;
		++cnt;
	}
	printf("\033[1;30m");
	printf("\ndivided into %d tokens\n", cnt);
	printf("\033[0m");
}

int	main(void)
{
	atexit(leak);
	t_list	*lst;
	char	*str;

	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		lst = tokenize(str);
		syntax_check(lst);
		print(lst);
		add_history(str);
		free(str);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?

// "g"r"epadasdasfasd"
