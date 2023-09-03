/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:46:05 by seunan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 21:38:36 by seunan           ###   ########.fr       */
=======
/*   Updated: 2023/08/27 23:06:45 by seunan           ###   ########.fr       */
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
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
<<<<<<< HEAD
		tmp->token = f(lst->token);
=======
		tmp->cmd = f(lst->cmd);
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (tmp->next == NULL)
		{
			ft_lstclear(&thead, del);
			return (NULL);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
<<<<<<< HEAD
	tmp->token = f(lst->token);
=======
	tmp->cmd = f(lst->cmd);
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
	return (thead);
}
