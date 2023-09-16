#include "minishell.h"

void	execute(t_list *lst)
{
	if (ft_strncmp(lst->token, "cd", 3) == 0)
		cd(lst);
	else if (ft_strncmp(lst->token, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(lst->token, "echo", 5) == 0)
		echo(lst);
}
