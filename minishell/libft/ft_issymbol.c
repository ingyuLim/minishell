/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issymbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:38:55 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:02:50 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_issymbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
