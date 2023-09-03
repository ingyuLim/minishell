/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:45:19 by seunan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 21:38:19 by seunan           ###   ########.fr       */
=======
/*   Updated: 2023/08/27 23:07:08 by seunan           ###   ########.fr       */
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
<<<<<<< HEAD
		del((*lst)->token);
=======
		del((*lst)->cmd);
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
		*lst = (*lst)->next;
		free(tmp);
	}
}
