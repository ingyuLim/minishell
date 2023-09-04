#include "minishell.h"

/*
2. 화이트스페이스 기준으로 쪼갠 단위 워드를 만들어 연결리스트에 넣는다.
	2-1. 만약 따옴표를 만나면 같은 따옴표를 만날때까지 모든 문자를 워드 취급한다.
		2-1-1. 따옴표가 닫힌 다음에 공백이 아니라면 화이트 스페이스를 만날 때 까지 모든 문자를 워드 취급한다.
	2-2. 만약 파이프를 만나면 리스트 넣고 다음 워드를 만든다.
	2-3. 만약 리다이렉션을 만나면 리스트 넣고 다음 워드를 만든다.

bash-3.2$ 'l''''''''s' => ls
bash-3.2$ ""gre"p" "a" => grep a
bash-3.2$ ""grep a"" => grep a
*/

void	add_token(t_list *lst, char *str, int *i)
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
			if (str[*i + 1] == '\0' || ft_iswhitespace(str[*i + 1]) || str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			{
				printf("%s\n", ft_substr(str, start, *i - start));
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, start, *i - start)));
				*i += 1;
				break ;
			}
			else
				*i += 1;
		}
		*i += 1;
	}
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
			add_token(lst, str, &i);
		else if (ft_iswhitespace(str[i]))			// 화이트 스페이스를 만날 때 까지 모든 문자를 워드 취급한다.
			i++;
		else if (str[i] == '|')						// 파이프를 만나면 리스트 넣고 다음 워드를 만든다.
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, 1)));
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')	// 리다이렉션을 만나면 리스트 넣고 다음 워드를 만든다.
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, 1)));
			i++;
		}
		else										// 그 외의 경우에는 모든 문자를 워드 취급한다.
		{
			int	start;

			start = i;
			while (str[i] != '\0' && !ft_iswhitespace(str[i]) && str[i] != '|' && str[i] != '<' && str[i] != '>')
				i++;
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, start, i - start)));
		}
	}
	return (lst);
}

void	print(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", lst->token);
		lst = lst->next;
	}
}

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;37mminishell$\033[0;31m>\033[0;m ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			printf("exit\n");
			break ;
		}
		print(parse(str));
		add_history(str);
		free(str);
	}
	return (0);
}
