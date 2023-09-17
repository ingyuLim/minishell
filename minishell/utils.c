#include "minishell.h"

void	leak(void)
{
	system("leaks minishell | grep leaked");
}

void	free_strtok(char *str, t_list **lst)
{
	free(str);
	ft_lstclear(lst, free);
}

void	print_tokens(t_list *lst)
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

