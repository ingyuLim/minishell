/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:55:43 by seunan            #+#    #+#             */
/*   Updated: 2023/10/05 21:56:08 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_origin(t_vars *vars)
{
	signal(SIGCHLD, child_handler);
	sigaction(SIGQUIT, NULL, &(vars->oact_quit));
	sigaction(SIGINT, NULL, &(vars->oact_int));
}
