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

	*i = *i + 1;
	idx = *i;
	len = 0;
	while(str[idx++] != quote)
		len++;
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	// printf("result in meet_quote = %s\n",result);
	return (result);
}

int ft_isspecial(char c)
{
	return(c == '|' || c == '<' || c == '>');
}

char	*ft_strpaste(char *front, char *back)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (front == NULL)
		return (NULL);
	result = (char *) ft_calloc((ft_strlen(front) + ft_strlen(back) + 1), \
	sizeof(char));
	if (result == NULL)
	{
		perror(NULL);
		exit(1);
	}
	j = 0;
	while (front[j] != '\0')
		result[i++] = front[j++];
	// free(front);
	j = 0;
	while (back[j] != '\0')
		result[i++] = back[j++];
	// free(back);
	return (result);
}

char *meet_word(char *str, int *i)
{
	int		idx;
	idx = *i;
	int len = 0;
	char *result;
	char *tmp;

	result = ft_calloc(1,sizeof(char));
	while(!ft_iswhitespace(str[idx]) && !ft_isspecial(str[idx]) && str[idx])
	{
		if(!ft_iswhitespace(str[idx]) && !ft_isspecial(str[idx]) && !ft_isquote(str[idx]) && str[idx])
		{
			len = 0;
			while(!ft_iswhitespace(str[idx]) && !ft_isspecial(str[idx]) && !ft_isquote(str[idx]) && str[idx])
			{
				idx++;
				len++;
			}
			tmp = gnl_strndup(str + (*i), len);
			printf("if tmp = %s\n",tmp);
			result = ft_strpaste(result,tmp);
			printf("if result = %s\n",result);
			*i = idx;
		}
		else if(ft_isquote(str[idx]))
		{
			tmp = meet_quote(str, &idx, str[idx]);
			printf("else tmp = %s\n",tmp);
			result = ft_strpaste(result,tmp);
			printf("else result = %s\n",result);
			*i = idx;
		}
	}
	// printf("%s\n",str+(*i));
	printf("result in meet_word = %s\n",result);
	return (result);
}


t_list	*organize_quote(char *str)
{
	// int keyword = 0;
	t_list	*head = NULL;
	char	*tmp;
	int i = 0;

	//일단은 쪼개서 합치는 방식.
	while(str[i])
	{
		while(ft_iswhitespace(str[i]))
			i++;
		if(ft_isquote(str[i]))
		{
			// printf("meet_quote\n");
			tmp = meet_quote(str, &i, str[i]);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if(ft_isspecial(str[i]))
		{
			tmp = ft_calloc(2,sizeof(char));
			tmp[0] = str[i];
			ft_lstadd_back(&head, ft_lstnew(tmp));
			i++;
		}
		else
		{
			// printf("meet_word\n");
			// printf("i = %d\n",i);
			tmp = meet_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		// printf("word = %s\n",tmp);
	}
	// printf("escape while\n");
	t_list *dummy = head;
	while(dummy)
	{
		printf("dummy->token = %s\n",dummy->token);
		dummy = dummy->next;
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
		organize_quote(str);
		add_history(str);
		free(str);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?

// "g"r"epadasdasfasd"