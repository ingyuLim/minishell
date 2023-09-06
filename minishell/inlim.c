#include "minishell.h"

int ft_isspecial(char c)
{
	return(c == '|' || c == '<' || c == '>' || c== ';');
}

int ft_isseparator(char c)
{
	return(ft_iswhitespace(c) || c == '\0' || ft_isspecial(c));
}

int ft_isword(char c)
{
	return(!ft_iswhitespace(c) && !ft_isspecial(c));
}

char	*gnl_strndup(char *src, int n)
{
	char	*dup;
	int		i;

	dup = (char *)ft_calloc(n + 1 , sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	return (dup);
}


char *meet_quote(char *str, int *i, char quote) //띄어쓰기까지 모두 문자 취급
{
	int		idx;
	int		len;
	char	*result;
	int flag = 0;

	*i = *i + 1;
	idx = *i;
	len = 0;
	while(str[idx] != quote && str[idx] != '\0')
	{
		len++;
		idx++;
	}
	if(str[idx] !=  quote)
	{
		printf("It doesn't match.\n");
		exit(1);
	}
	result = gnl_strndup(str + (*i), len);
	*i = idx + 1;
	// printf("result in meet_quote = %s\n",result);
	return (result);
}

char *meet_charactor(char *str, int *i)
{
	char *result;
	int len = 0;
	int idx = *i;

	// printf("meet_charactor\n");
	while(!ft_isseparator(str[idx]) && !ft_isquote(str[idx]))
	{
		idx++;
		len++;
	}
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	return result;
}

char *meet_word(char *str, int *i)
{
	int idx;
	char *tmp;
	char *result = ft_calloc(1, sizeof(char));
	idx = *i;

	// printf("meet_word\n");

	while(!ft_isseparator(str[idx])) //구분자가 나오기 전까진 한 덩어리.
	{
		if(ft_isquote(str[idx]))
		{
			tmp = meet_quote(str, &idx, str[idx]);
		}
		else
		{
			tmp = meet_charactor(str, &idx);
		}
		// if(tmp != NULL)
			result = ft_strjoin(result,tmp);
	}
	*i = idx;
	return result;
}

char *meet_special(char *str, int *i)
{
	int n = 0;
	int idx;
	char *result;

	idx = *i;
	while(ft_isspecial(str[idx + n]))
		{
			n++;
			if(n > 2)
				exit(1);
		}
	result = ft_calloc(n + 1, sizeof(char));
	ft_strlcpy(result, str + idx, n + 1);
	*i = idx + n;
	return result;
}


t_list *organize_syntax(char *str)
{
	t_list *head = NULL;
	int start_flag = 0;
	int i = 0;
	char *tmp;
	int len = 0;
	// printf("organize_syntax\n");
	while(ft_iswhitespace(str[i]))
		i++;
	while(str[i] != '\0')
	{
		if(ft_isspecial(str[i]))
		{
			tmp = meet_special(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if(ft_isword(str[i]))
		{
			// printf("isword\n");
			tmp = meet_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else//ws이면.
			i++;
	}

	t_list *test;
	test = head;
	while(test)
	{
		printf("test->token = %s\n",test->token);
		test=test->next;
	}
	return head;
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
		organize_syntax(str);
		add_history(str);
		free(str);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?
