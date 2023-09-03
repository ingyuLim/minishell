/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:45:54 by seunan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 21:38:27 by seunan           ###   ########.fr       */
=======
/*   Updated: 2023/08/27 23:07:00 by seunan           ###   ########.fr       */
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
<<<<<<< HEAD
		f(lst->token);
=======
		f(lst->cmd);
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
		lst = lst->next;
	}
}
