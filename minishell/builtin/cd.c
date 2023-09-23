#include "../minishell.h"

int	b_cd(char **cmd)
{
	//1. lst 진짜 옮기기
	//2. 마지막 cmd인 경우 flag를 줘서 fork 하지 않게 하기.
	char	*path;

	if (cmd[1] == NULL || ft_strncmp(cmd[1], "~", 2) == 0 || ft_isspecialtok(cmd[1] == 1))
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
