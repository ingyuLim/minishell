/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:39:51 by seunan            #+#    #+#             */
/*   Updated: 2023/10/09 00:43:14 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_count(t_list *lst)
{
	int	process;

	process = 1;
	while (lst != NULL)
	{
		if (ft_strncmp(lst->token, "|", 2) == 0)
			process++;
		lst = lst->next;
	}
	return (process);
}

int	cmd_size_count(t_list *lst)
{
	int	size;

	size = 1;
	while (lst != NULL && ft_strncmp(lst->token, "|", 2) != 0)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	count_cmd_count(t_list *lst)
{
	int	len;

	len = 1;
	while (lst != NULL && ft_strncmp((lst)->token, "|", 2) != 0)
	{
		if (lst->state == CMD)
			len++;
		lst = (lst)->next;
	}
	return (len);
}

size_t	gnl_strlen(char *str)
{
	int	result_len;

	result_len = 0;
	while (*str)
	{
		result_len++;
		if (*str == '\n')
			break ;
		str++;
	}
	return (result_len);
}

int	ent_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
		env = env->next;
	return (i);
}
