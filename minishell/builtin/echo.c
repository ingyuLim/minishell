#include "../minishell.h"

int	b_echo(t_list **lst)
{
	int	flag;

	flag = 0;
	*lst = (*lst)->next;
	if(*lst != NULL && ft_strncmp("-n", (*lst)->token, 3) == 0)
	{
		*lst = (*lst)->next;
		flag = 1;
	}
	while(*lst != NULL && ft_isspecialtok((*lst)->state) == 0)
	{
		ft_putstr_fd((*lst)->token, 1);
		if((*lst)->next != NULL)
			ft_putchar_fd(' ', 1);
		*lst = (*lst)->next;
	}
	if(flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
