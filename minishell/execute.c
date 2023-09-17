#include "minishell.h"

void	builtin_fuc(t_vars *vars, t_list *lst)
{
	if (ft_strncmp(lst->token, "cd", 3) == 0)
		b_cd(lst);
	else if (ft_strncmp(lst->token, "pwd", 4) == 0)
		b_pwd();
	else if (ft_strncmp(lst->token, "echo", 5) == 0)
		b_echo(lst);
	else if (ft_strncmp(lst->token, "export", 7) == 0)
		b_export(lst, vars->env);
	else if (ft_strncmp(lst->token, "env", 4) == 0)
		b_env(lst, vars->env);
	// else if (ft_strncmp(lst->token, "unset", 6) == 0)
	// 	b_unset(lst, vars->env);
	else if (ft_strncmp(lst->token, "exit", 5) == 0)
		b_exit(0);
}

void	execute(t_vars *vars)
{
	t_list	*tmp;

	tmp = vars->lst;
	builtin_fuc(vars, tmp);
}
