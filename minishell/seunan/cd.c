#include "../minishell.h"

void	cd(t_list *cmd)
{
	char	*path;

	cmd = cmd->next;
	if (cmd == NULL || ft_strncmp(cmd->token, "~", 2) == 0)
		path = getenv("HOME");
	else
		path = cmd->token;
	if (chdir(path) == -1)
		error(path);
}
