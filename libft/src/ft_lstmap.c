/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:46:05 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:32:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*thead;

	tmp = ft_calloc(1, sizeof(t_list));
	if (lst == NULLPTR || tmp == NULLPTR)
		return (NULLPTR);
	thead = tmp;
	while (lst->next != NULLPTR)
	{
		tmp->token = f(lst->token);
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (tmp->next == NULLPTR)
		{
			ft_lstclear(&thead, del);
			return (NULLPTR);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->token = f(lst->token);
	return (thead);
}
