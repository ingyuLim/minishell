#include"minishell.h"

void	execute(t_list *head)
{
	t_list	*tmp;
	char	**cmd;
	int		i;
	int 	n;

	tmp = head;
	while(tmp != NULL)
	{
		n = 0;
		while(tmp != NULL && tmp->token != '|')
		{
			n++;
			tmp = tmp->next;
		}
		if(tmp != NULL)
			tmp = tmp->next;
		cmd = (char **)ft_calloc(n + 1 , sizeof(char *));
		// 실제로 if(cmd == NULL) 이면 어떡하지?
		i = 0;
		while(i < n)
		{
			cmd[i++] = head->token;
			head = head->next;
		}
	}
}