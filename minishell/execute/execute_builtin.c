#include "../minishell.h"

int	is_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	builtin_func(t_vars *vars, char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		g_status = b_cd(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		g_status = b_pwd();
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		g_status = b_echo(cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		g_status = b_export(cmd, vars->env);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		g_status = b_env(vars->env);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		g_status = b_unset(cmd, &(vars->env));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		g_status = b_exit(cmd);
	return (g_status);
}
