/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:39:43 by seunan            #+#    #+#             */
/*   Updated: 2023/10/13 16:24:54 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_variable(t_vars *vars, t_list **lst, t_execute *data)
{
	int	stdin_fd;

	stdin_fd = dup(0);
	*lst = vars->lst;
	data->pid_index = 0;
	data->tmp_arr = malloc_tmp_arr(*lst);
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	fill_tmp_arr(data->tmp_arr, *lst);
	data->tmp_arr_index = 0;
	data->envp = make_envp(vars->env);
	dup2(stdin_fd, 0);
	signal(SIGINT, sigint_handler_exec);
	signal(SIGQUIT, sigquit_handler_exec);
}

char	**make_cmd(t_list *lst)
{
	int		i;
	int		cmd_len;
	char	**cmd;

	i = 0;
	cmd_len = count_cmd_count(lst);
	cmd = ft_calloc(cmd_len + 1, sizeof(char *));
	while (lst != NULL && lst->state != PIPE)
	{
		if (lst->state == CMD)
		{
			cmd[i] = (lst)->token;
			i++;
		}
		lst = (lst)->next;
	}
	return (cmd);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	char	*mem;
	int		i;

	i = ent_size(env);
	envp = (char **)ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			mem = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(mem, env->value);
			use_free(mem);
			++i;
		}
		env = env->next;
	}
	return (envp);
}

char	*path_join(char **path, char *cmd)
{
	char		*tmp;
	struct stat	buf;
	int			i;

	if (path == NULL)
		return (cmd);
	i = 0;
	if (!cmd || *cmd == '\0')
		return (cmd);
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], cmd);
		stat(tmp, &buf);
		if (access(tmp, X_OK) == 0 && S_ISREG(buf.st_mode))
			break ;
		use_free(tmp);
		++i;
	}
	if (path[i] == NULL)
		return (cmd);
	return (tmp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		use_free(envp[i]);
		++i;
	}
	use_free(envp);
}
