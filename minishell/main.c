#include "minishell.h"

char	*find_pair(char *str, char quote)
{

}

/*
1. 문자를 만날 때까지 화이트스페이스를 민다.
2. 화이트스페이스 기준으로 쪼갠 단위 워드를 만들어 연결리스트에 넣는다.
	2-1. 만약 따옴표를 만나면 같은 따옴표를 만날때까지 모든 문자를 워드 취급한다.
		2-1-1. 따옴표가 닫힌 다음에 공백이 아니라면 화이트 스페이스를 만날 때 까지 모든 문자를 워드 취급한다.
	2-2. 만약 파이프를 만나면 리스트 넣고 다음 워드를 만든다.
	2-3. 만약 리다이렉션을 만나면 리스트 넣고 다음 워드를 만든다.

bash-3.2$ 'l''''''''s' => ls
bash-3.2$ ""gre"p" "a" => grep a
bash-3.2$ ""grep a"" => grep a
*/


t_list	*parse(char *str)
{
	t_list	*lst;
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]))
			find_pair(str + i, str[i]);
		++i;
	}
	return (lst);
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
		printf("%s\n",str);
		parse(str);
		add_history(str);
		free(str);
	}
	return (0);
}
