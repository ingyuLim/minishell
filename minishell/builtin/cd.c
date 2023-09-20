#include "../minishell.h"

int	b_cd(t_list **lst)
{
	//1. lst 진짜 옮기기
	//2. 마지막 cmd인 경우 flag를 줘서 fork 하지 않게 하기.
	char	*path;

	*lst = (*lst)->next;
	if (*lst == NULL || ft_strncmp((*lst)->token, "~", 2) == 0 || ft_isspecialtok((*lst)->state) == 1)
		path = getenv("HOME");
	else
	{
		path = (*lst)->token;
		while ((*lst) != NULL && ft_isspecialtok((*lst)->state) == 0)
			*lst = (*lst)->next;
	}
	if (chdir(path) == -1)
	{
		error(path);
		return (1);
	}
	return (0);
}
