/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:01:02 by seunan            #+#    #+#             */
/*   Updated: 2023/10/11 18:50:30 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_state state)
{
	if (state == CMD || state == FNAME)
		return (1);
	return (0);
}

void	change_state(t_state *cur, t_state *lst, t_state state)
{
	*cur = state;
	*lst = state;
}

int	last_condition(t_list *lst)
{
	if (ft_strncmp(lst->token, "|", 2) != 0
		&& ft_strncmp(lst->token, "<", 2) != 0
		&& ft_strncmp(lst->token, ">", 2) != 0)
		return (1);
	return (0);
}
