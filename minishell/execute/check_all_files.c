#include "../minishell.h"

int	check_slash(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (0);
		cmd++;
	}
	return (1);
}

char	*plus_slash(char *cmd)
{
	char	*result;
	int		i;

	i = 1;
	result = (char *)ft_calloc(ft_strlen(cmd) + 2, sizeof(char));
	if (result == NULL)
		return (NULL);
	result[0] = '/';
	while (cmd[i - 1])
	{
		result[i] = cmd[i - 1];
		i++;
	}
	free(cmd);
	return (result);
}

int	absolute_path(char **cmd)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (cmd[0] == NULL)
			exit(1);
		return (1);
	}
	return (0);
}

int	relative_path(char	**cmd, char	**path)
{
	int		i;
	char	*new_cmd;

	i = 0;
	cmd[0] = plus_slash(cmd[0]);
	if (cmd[0] == NULL)
	{
		perror(NULL);
		exit(1);
	}
	new_cmd = ft_strjoin(path[i], cmd[0]);
	++i;
	while (new_cmd > 0) //!=NULL?
	{
		if (access(new_cmd, X_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = new_cmd;
			return (1);
		}
		free(new_cmd);
		new_cmd = ft_strjoin(path[i], cmd[0]);
		++i;
	}
	return (0);
}

void	check_xfile(char **cmd, char **path)
{
	// char **tmp = cmd;
	// while(*tmp)
	// {
	// 	printf("%s\n", *tmp);
	// 	tmp++;
	// }
	if (check_slash(cmd[0]) != 0)
	{
		if (relative_path(cmd, path))
		{
			return ;
		}
	}
	else
	{
		if (absolute_path(cmd))
			return ;
	}
	perror("Command not found");
	exit(1);
}
