#include "../minishell.h"

void echo(t_list *cmd)
{
	int	flag = 0;
	cmd = cmd->next;
	if (cmd == NULL)
	{
		write(1,"\n",1);
		return ;
	}
	if(ft_strncmp("-n", cmd->token, 3) == 0)
	{
		cmd = cmd->next;
		flag = 1;
	}
	while(cmd != NULL)
	{
		ft_putstr_fd(cmd->token, 1);
		if(cmd->next != NULL)
			write(1," ",1);
		cmd = cmd->next;
	}
	if(flag == 0)
		write(1,"\n",1);
}
