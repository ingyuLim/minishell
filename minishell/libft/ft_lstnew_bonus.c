/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:41 by seunan            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 21:41:55 by seunan           ###   ########.fr       */
=======
/*   Updated: 2023/08/27 23:06:13 by seunan           ###   ########.fr       */
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
<<<<<<< HEAD
	new->token = content;
=======
	new->cmd = content;
>>>>>>> 5410290b7d2ddc3ca8b0114d21a4e8cb63c408f1
	new->next = NULL;
	return (new);
}
