/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:36:07 by seunan            #+#    #+#             */
/*   Updated: 2023/10/14 17:19:25 by seunan           ###   ########.fr       */
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

void	fill_heredoc(int *len, int buffer_size, int tmp_fd, char *limiter)
{
	char	*buf;
	int		nl_flag;

	buf = ft_calloc(buffer_size + 1, sizeof(char));
	nl_flag = 1;
	*len = read(0, buf, buffer_size);
	buf[buffer_size] = '\0';
	while (*len > 0)
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
		*len = read(0, buf, buffer_size);
		buf[buffer_size] = '\0';
	}
	use_free(buf);
}

void	write_in_tmpfile(t_list *lst, int tmp_fd, int *len)
{
	char	*limiter;
	size_t	buffer_size;

	limiter = lst->next->token;
	buffer_size = ft_strlen(limiter) + 1;
	ft_putstr_fd("\033[0;30m> ", 1);
	fill_heredoc(len, buffer_size, tmp_fd, limiter);
}

void	fill_tmp_arr(char **tmp_arr, t_list *lst)
{
	int		i;
	char	*tmp_filename;
	int		tmp_fd;
	int		len;

	i = 0;
	len = 0;
	tmp_filename = NULL;
	while (lst != NULL)
	{
		if (lst->state == HEREDOC)
		{
			tmp_filename = naming_tmp_file(".tmp");
			tmp_fd = open(tmp_filename, O_RDWR | O_CREAT, 0644);
			tmp_arr[i] = tmp_filename;
			if (len != -1)
				write_in_tmpfile(lst, tmp_fd, &len);
			use_close(tmp_fd);
			i++;
		}
		lst = lst->next;
	}
	ft_putstr_fd("\033[0m", 1);
}
