#include "minishell.h"

/*
1. 화이트스페이스 기준으로 쪼갠 단위 워드를 만들어 연결리스트에 넣는다.
	1-1. 만약 따옴표를 만나면 같은 따옴표를 만날때까지 모든 문자를 워드 취급한다.
		1-1-1. 따옴표가 닫힌 다음에 공백이 아니라면 화이트 스페이스를 만날 때 까지 모든 문자를 워드 취급한다.
	1-2. 만약 파이프를 만나면 리스트 넣고 다음 워드를 만든다.
	1-3. 만약 리다이렉션을 만나면 리스트 넣고 다음 워드를 만든다.

bash-3.2$ 'l''''''''s' => ls
bash-3.2$ ""gre"p" "a" => grep a
bash-3.2$ ""grep a"" => grep a
*/

char	*ft_substr_exclude(char const *s, unsigned int start, size_t len, char exclude)
{
	char	*str;
	size_t	i;
	size_t	size;
	size_t	start_cpy;

	size = 0;
	i = 0;
	start_cpy = start;
	while (s[start] != '\0' && i < len && start_cpy < ft_strlen(s))
	{
		if (s[start_cpy] != exclude)
			++size;
		++start_cpy;
		++i;
	}
	i = 0;
	str = (char *) ft_calloc(size + 1, sizeof(char));
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		if (str[start] != exclude)
		{
			str[i] = s[start];
			++start;
		}
		++i;
	}
	return (str);
}

void	quote(t_list *lst, char *str, int *i)
{
	char	quote;
	int		start;

	quote = str[*i];
	*i += 1;
	start = *i;
	while (str[*i] != '\0')
	{
		if (str[*i] == quote)
		{
			if (str[*i + 1] == '\0' || ft_iswhitespace(str[*i + 1]) || str[*i + 1] == '|' || str[*i + 1] == '<' || str[*i + 1] == '>')
				break ;
			else
				*i += 1;
		}
		*i += 1;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr_exclude(str, start, *i - start, quote)));
	*i += 1;
}

t_list	*parse(char *str)
{
	t_list	*lst;
	int	i;

	lst = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]))						// 따옴표를 만나면 같은 따옴표를 만날때까지 모든 문자를 워드 취급한다.
			quote(lst, str, &i);
		else if (ft_iswhitespace(str[i]))			// 화이트 스페이스를 만날 때 까지 모든 문자를 워드 취급한다.
			i++;
		else if (str[i] == '|')						// 파이프를 만나면 리스트 넣고 다음 워드를 만든다.
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, 1)));
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')	// 리다이렉션을 만나면 리스트 넣고 다음 워드를 만든다.
		{
			if (str[i + 1] == str[i])
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, 2)));
				i += 2;
			}
			else
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, 1)));
				i++;
			}
		}
		else										// 그 외의 경우에는 모든 문자를 워드 취급한다.
		{
			int	start;

			start = i;
			while (str[i] != '\0' && !ft_iswhitespace(str[i]) && str[i] != '|' && str[i] != '<' && str[i] != '>' && !ft_isquote(str[i]))
				i++;
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, start, i - start)));
		}
	}
	return (lst);
}
