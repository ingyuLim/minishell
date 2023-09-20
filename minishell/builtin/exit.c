#include "../minishell.h"

int	b_exit(t_list **lst)
{
	*lst = (*lst)->next;
	if (*lst == NULL)
		exit(0);
	exit(ft_atoi((*lst)->token));
}
