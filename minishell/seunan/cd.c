#include "../minishell.h"

void	cd(t_list *cmd)
{
	char	*path;

	cmd = cmd->next;
	if (cmd == NULL)
		path = getenv("HOME");
	else
	{
		path = cmd->token;
		if (path[0] == '~')
			path = ft_strjoin(getenv("HOME"), path + 1);
	}
	if (chdir(path) == -1)
		perror(path);
}
