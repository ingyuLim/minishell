/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:46:05 by seunan            #+#    #+#             */
/*   Updated: 2023/08/27 23:06:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*thead;

	tmp = ft_calloc(1, sizeof(t_list));
	if (lst == NULL || tmp == NULL)
		return (NULL);
	thead = tmp;
	while (lst->next != NULL)
	{
		tmp->cmd = f(lst->cmd);
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (tmp->next == NULL)
		{
			ft_lstclear(&thead, del);
			return (NULL);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->cmd = f(lst->cmd);
	return (thead);
}
