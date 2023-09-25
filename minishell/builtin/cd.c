#include "../minishell.h"

int	b_cd(char **cmd)
{
	char	*path;

	if (cmd[1] == NULL || ft_strncmp(cmd[1], "~", 2) == 0)
		path = getenv("HOME");
	else
		path = cmd[1];
	if (chdir(path) == -1)
	{
		error(path);
		return (1);
	}
	return (0);
}
