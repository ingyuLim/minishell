#include "minishell.h"

// 따옴표를 만날 때까지의 길이를 구한다.
char *meet_quote(char *str, int *i, char quote)
{
	char	*result;
	int		last;
	int		len;

	last = *i + 1;
	len = 2;
	while(str[last] != quote) // 짝이 맞는 따옴표를 만날 때까지의 길이를 구한다.
	{
		if(str[last] == '\0')
			exit_with_msg("It doesn't match\n");
		len++;
		last++;
	}
	result = ft_substr(str, *i, len);
	*i = last + 1;
	return (result);
}

char *meet_sep(char *str, int *i)
{
	char	*result;
	int		len;
	int		last;

	last = *i;
	len  = 0;
	while(!ft_isseparator(str[last]) && !ft_isquote(str[last]))
	{
		last++;
		len++;
	}
	result = ft_substr(str, *i, len);
	*i = last;
	return result;
}

// '|' '<' '>' whitespace가 아닐 경우 => ", ', 문자일 경우
char *make_word(char *str, int *i)
{
	int		last; // 마지막 인덱스
	char	*tmp;
	char	*mem;
	char	*result;

	result = ft_calloc(1, sizeof(char));
	last = *i;
	while(ft_isword(str[last])) // == !ft_isseparator(str[last])
	{
		if (ft_isquote(str[last])) // 따옴표일 경우
			tmp = meet_quote(str, &last, str[last]);
		else
			tmp = meet_sep(str, &last);
		mem = result;
		result = ft_strjoin(result,tmp);
		free(mem);
	}
	*i = last;
	return (result);
}

// '|' '<' '>' 일 경우
char *make_symbol(char *str, char c, int *i)
{
	char	*result;
	int		len;

	if (str[*i] == '|' && str[*i + 1] == '|')
		exit_with_msg("syntax error near unexpected token\n");
	len = 1;
	while(str[*i + len] == c)
	{
		len++;
		if(len > 2)
			exit_with_msg("syntax error near unexpected token\n");
	}
	result = ft_substr(str, *i, len);
	*i += len;
	return (result);
}

t_list	*tokenize(char *str)
{
	t_list	*head;
	char	*tmp;
	int		i;

	i = 0;
	head = NULL;
	while(str[i] != '\0')
	{
		if(ft_issymbol(str[i]))
		{
			tmp = make_symbol(str, str[i], &i); // leak없음
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if(ft_isword(str[i]))
		{
			tmp = make_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else // whitespace일 경우
			i++;
	}
	return (head);
}
