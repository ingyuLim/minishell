/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:36:07 by seunan            #+#    #+#             */
/*   Updated: 2023/10/02 21:36:53 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**malloc_tmp_arr(t_list *lst)
{
	char	**tmp_arr;
	int		i;

	tmp_arr = NULL;
	i = 0;
	while (lst != NULL)
	{
		if (lst->state == HEREDOC)
			i++;
		lst = (lst)->next;
	}
	if (i != 0)
		tmp_arr = ft_calloc(i + 1, sizeof(char *));
	return (tmp_arr);
}

char	*naming_tmp_file(char *tmp_file)
{
	int		num;
	char	*letter_num;
	char	*tmp_filename;

	num = 0;
	letter_num = ft_itoa(num++);
	tmp_filename = ft_strjoin(tmp_file, letter_num);
	use_free(letter_num);
	while (access(tmp_filename, F_OK) != -1)
	{
		if (tmp_filename != NULL)
			use_free(tmp_filename);
		letter_num = ft_itoa(num++);
		tmp_filename = ft_strjoin(tmp_file, letter_num);
		use_free(letter_num);
	}
	return (tmp_filename);
}

void	write_in_tmpfile(t_list *lst, int tmp_fd)
{
	char	*limiter;
	size_t	buffer_size;
	char	*buf;
	int		nl_flag;

	limiter = lst->next->token;
	buffer_size = ft_strlen(limiter) + 1;
	buf = ft_calloc(buffer_size, sizeof(char));
	nl_flag = 1;
	ft_putstr_fd("\033[0;30m> ", 1);
	while (read(0, buf, buffer_size))
	{
		if (!ft_strncmp(limiter, buf, buffer_size - 1)
			&& buf[buffer_size - 1] == '\n' && nl_flag)
			break ;
		else if (ft_strchr(buf, '\n'))
		{
			nl_flag = 1;
			ft_putstr_fd("> ", 1);
		}
		else
			nl_flag = 0;
		write(tmp_fd, buf, gnl_strlen(buf));
	}
	use_free(buf);
}

void	fill_tmp_arr(char **tmp_arr, t_list *lst)
{
	int		i;
	char	*tmp_filename;
	int		tmp_fd;

	i = 0;
	tmp_filename = NULL;
	while (lst != NULL)
	{
		if (lst->state == HEREDOC)
		{
			tmp_filename = naming_tmp_file(".tmp");
			tmp_fd = open(tmp_filename, O_RDWR | O_CREAT, 0644);
			tmp_arr[i] = tmp_filename;
			write_in_tmpfile(lst, tmp_fd);
			use_close(tmp_fd);
			i++;
		}
		lst = lst->next;
	}
	ft_putstr_fd("\033[0m", 1);
}

void	free_tmp_arr(char **tmp_arr)
{
	int	i;

	i = 0;
	while (tmp_arr[i] != NULL)
	{
		use_free(tmp_arr[i]);
		i++;
	}
	use_free(tmp_arr);
}
