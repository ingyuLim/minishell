/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:11 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:38:43 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	b_export(char **cmd, t_env **env)
{
	int		i;
	int		res;

	res = 0;
	if (cmd[1] == NULL)
		print_export(*env);
	else
	{
		i = 1;
		while (cmd[i] != NULL)
		{
			res = add_env(env, cmd[i]);
			++i;
		}
	}
	return (res);
}

int	add_env(t_env **env, char *cmd)
{
	t_env	*e_tmp;

	e_tmp = *env;
	while (e_tmp != NULL)
	{
		if (ft_strncmp(e_tmp->key, cmd, ft_strlen(e_tmp->key)) == 0
			&& cmd[ft_strlen(e_tmp->key)] == '=')
		{
			use_free(e_tmp->value);
			e_tmp->value = ft_strdup(cmd + ft_strlen(e_tmp->key) + 1);
			break ;
		}
		else if (ft_strncmp(e_tmp->key, cmd, ft_strlen(e_tmp->key) + 1) == 0)
			break ;
		e_tmp = e_tmp->next;
	}
	return (ft_isvalidenv(env, cmd, e_tmp));
}

int	ft_isvalidenv(t_env **env, char *cmd, t_env *e_tmp)
{
	if (e_tmp == NULL)
	{
		if (!ft_isvalidkey(cmd))
		{
			error_msg("not a valid identifier", "export", cmd);
			return (1);
		}
		else
			ft_envadd_back(env, make_env(cmd));
	}
	return (0);
}

void	print_export(t_env *env)
{
	while (env != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
}

void	print_quote(int flag)
{
	if (flag == 1)
		ft_putchar_fd('\"', STDOUT_FILENO);
	else if (flag == 2)
		ft_putchar_fd('\'', STDOUT_FILENO);
}
