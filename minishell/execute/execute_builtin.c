/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:37:05 by seunan            #+#    #+#             */
/*   Updated: 2023/10/03 21:32:12 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_onlybuiltin(t_execute data, t_list *lst, int process)
{
	if (is_builtin(data.cmd) && data.pid_index == process - 1
		&& data.pid_index == 0 && !ft_is_redirection(lst))
		return (1);
	return (0);
}

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
		g_status = b_export(cmd, &(vars->env));
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		g_status = b_env(vars->env);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		g_status = b_unset(cmd, &(vars->env));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		g_status = b_exit(cmd);
	return (g_status);
}
