/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:01:16 by seunan            #+#    #+#             */
/*   Updated: 2023/10/02 01:30:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*tokenize(char *str)
{
	t_list	*head;
	char	*tmp;
	int		i;

	i = 0;
	head = NULL;
	while (str[i] != '\0')
	{
		if (ft_issymbol(str[i]))
		{
			tmp = make_symbol(str, str[i], &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if (ft_isword(str[i]))
		{
			tmp = make_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else
			i++;
	}
	return (head);
}

char	*make_word(char *str, int *i)
{
	int		last;
	char	*tmp;
	char	*mem;
	char	*result;

	result = ft_strdup("");
	last = *i;
	while (ft_isword(str[last]))
	{
		if (ft_isquote(str[last]))
			tmp = meet_quote(str, &last, str[last]);
		else
			tmp = meet_sep(str, &last);
		mem = result;
		result = ft_strjoin(result, tmp);
		use_free(tmp);
		use_free(mem);
	}
	*i = last;
	return (result);
}

char	*make_symbol(char *str, char c, int *i)
{
	char	*result;
	int		len;

	len = 1;
	if (c == '|')
	{
		result = ft_substr(str, *i, len);
		*i += len;
		return (result);
	}
	while (str[*i + len] == c)
	{
		len++;
		if (len >= 2)
			break ;
	}
	result = ft_substr(str, *i, len);
	*i += len;
	return (result);
}

char	*meet_quote(char *str, int *i, char quote)
{
	int	start;
	int	len;

	start = *i;
	++(*i);
	len = 1;
	while (str[*i] != '\0' && str[*i] != quote)
	{
		++len;
		++(*i);
	}
	++(*i);
	return (ft_substr(str, start, len + 1));
}

char	*meet_sep(char *str, int *i)
{
	char	*result;
	int		len;
	int		last;

	last = *i;
	len = 0;
	while (!ft_isseparator(str[last]) && !ft_isquote(str[last]))
	{
		last++;
		len++;
	}
	result = ft_substr(str, *i, len);
	*i = last;
	return (result);
}
