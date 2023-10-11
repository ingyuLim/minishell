/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:40:02 by seunan            #+#    #+#             */
/*   Updated: 2023/10/11 16:43:24 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_in_redir(t_list **lst)
{
	int	infile_fd;

	*lst = (*lst)->next;
	infile_fd = open((*lst)->token, O_RDONLY);
	if (infile_fd == -1)
		exit_with_err((*lst)->token, 0, 1);
	use_dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}

void	find_out_redir(t_list **lst)
{
	int	outfile_fd;

	*lst = (*lst)->next;
	outfile_fd = open((*lst)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_with_err((*lst)->token, 0, 1);
	use_dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	find_heredoc(char **tmp_arr, int *tmp_arr_index)
{
	int	infile_fd;

	infile_fd = open(tmp_arr[*tmp_arr_index], O_RDONLY);
	use_dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	unlink(tmp_arr[*tmp_arr_index]);
	(*tmp_arr_index)++;
}

void	find_pair_out_redir(t_list **lst)
{
	int	outfile_fd;

	*lst = (*lst)->next;
	outfile_fd = open((*lst)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd == -1)
		exit_with_err((*lst)->token, 0, 1);
	use_dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	find_redirect(t_list *lst, char **tmp_arr, int *tmp_arr_index)
{
	while (lst != NULL && lst->state != PIPE)
	{
		if (lst->state == IN_REDIR)
			find_in_redir(&lst);
		else if (lst->state == OUT_REDIR)
			find_out_redir(&lst);
		else if (lst->state == HEREDOC)
			find_heredoc(tmp_arr, tmp_arr_index);
		else if (lst->state == PAIR_OUT_REDIR)
			find_pair_out_redir(&lst);
		lst = lst->next;
	}
}
