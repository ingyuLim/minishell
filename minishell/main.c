#include "minishell.h"

void	print(void *content)
{
	printf("%s\n", content);
}

int	is_separator(char c)
{
	if (ft_iswhitespace(c) || c == '|' || c == '\0')
		return (1);
	return (0);
}

void	add_token(t_list **token, char *str, int start, int end)
{
	char	*content;

	content = ft_substr(str, start, end - start);
	ft_lstadd_back(token, ft_lstnew(content));
}

void	tokenize(char *str)
{
	t_list	*token;
	int		start;
	int		i;
	int		quote[2]; // quote가 참이면 열려있는 상태

	token = NULL;
	quote[SINGLE] = 0;
	quote[DOUBLE] = 0;
	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote[SINGLE] = !quote[SINGLE];
		if (str[i] == '\"')
			quote[DOUBLE] = !quote[DOUBLE];
		if (is_separator(str[i + 1]) && quote[SINGLE] == 0 && quote[DOUBLE] == 0)
		{
			add_token(&token, str, start, i + 1);
			start = i + 2;
			i = start;
		}
		i++;
	}
	ft_lstiter(token, print);
}

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;37mminishell$\033[0;31m>\033[0;m ");
		if (ft_strncmp(str, "exit", 5) == 0)
			break ;
		tokenize(str);
		add_history(str);
		free(str);
	}
	return (0);
}
