#include "minishell.h"

void	execute(t_list *lst, char *envp[])
{
	if (ft_strncmp(lst->token, "cd", 3) == 0)
		cd(lst);
	else if (ft_strncmp(lst->token, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(lst->token, "echo", 5) == 0)
		echo(lst);
	else if (ft_strncmp(lst->token, "export", 7) == 0)
		export(lst, envp);
	else if (ft_strncmp(lst->token, "env", 4) == 0)
		env(lst, envp);
}
