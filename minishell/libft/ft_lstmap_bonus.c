/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:46:05 by seunan            #+#    #+#             */
/*   Updated: 2023/03/18 13:32:16 by seunan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*thead;

	tmp = ft_calloc(1, sizeof(t_list));
	if (lst == 0 || tmp == 0)
		return (0);
	thead = tmp;
	while (lst->next != 0)
	{
		tmp->content = f(lst->content);
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (tmp->next == 0)
		{
			ft_lstclear(&thead, del);
			return (0);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->content = f(lst->content);
	return (thead);
}
