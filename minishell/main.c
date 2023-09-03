#include "minishell.h"

char	*gnl_strndup(char *src, int n)
{
	char	*dup;
	int		i;

	dup = (char *)ft_calloc(n + 1 , sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = src[i];
		i++;
	}
	return (dup);
}

int	even(int n)
{
	if (n % 2 == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

char *meet_quote(char *str, int *i, char quote) //띄어쓰기까지 모두 문자 취급
{
	int		idx;
	int		len;
	char	*result;

	idx = *i + 1;
	len = 0;
	while(str[idx++] != quote)
		len++;
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	return (result);
}

char *meet_char(char *str)
{
	int i = 0;
	int len = 0;
	char *result;

	while(!ft_iswhitespace(str[i]) && !ft_isquote(str[i]))
	{
		i++;
		len++;
	}
	result = gnl_strndup(str, len);
	return (result);
}

char	**organize_quote(char *str)
{
	t_list	*head;
	t_list	*lst_tmp;
	char	*tmp;
	int i = 0;
	char **result;
	int size;

	//일단은 쪼개서 합치는 방식.
	while(str[i])
	{
		while(ft_iswhitespace(str[i]))
			i++;
		if(ft_isquote(str[i]))
		{
			tmp = meet_quote(str, &i, str[i]);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else
		{
			tmp = meet_char(str + i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		i++;
	}
	size = ft_lstsize(head) + 1;
	result = (char **)ft_calloc(sizeof(char *), size);
	lst_tmp = head;
	i = 0;
	while(lst_tmp)
	{
		result[i++] = lst_tmp->token;
		lst_tmp = lst_tmp->next;
	}
	return result;
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
		printf("%s",str);
		organize_quote(str);
		add_history(str);
		free(str);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?
