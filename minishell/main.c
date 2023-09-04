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

	idx = *i;
	len = 0;
	while(str[idx++] != quote)
		len++;
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	return (result);
}

char *meet_word(char *str, int *i)
{
	int		idx;
	idx = *i;
	int len = 0;
	char *result;

	while(!ft_iswhitespace(str[idx]) && !ft_isquote(str[idx]) && str[idx])
	{
		idx++;
		len++;
	}
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	printf("result in meet_word = %s\n",result);
	return (result);
}

char	*organize_quote(char *str)
{
	t_list	*head = NULL;
	t_list	*lst_tmp;
	int len = 0;
	char	*tmp;
	int i = 0;
	char *result;
	while(ft_iswhitespace(str[i]))
		i++;
	//일단은 쪼개서 합치는 방식.
	while(str[i])
	{
		if(ft_isquote(str[i]))
		{
			// printf("meet_quote\n");
			tmp = meet_quote(str, &i, str[i]);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if(ft_iswhitespace(str[i]))
		{
			// printf("meet_ws\n");
			while(ft_iswhitespace(str[i]))
				i++;
			tmp = " ";
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else
		{
			// printf("meet_word\n");
			printf("i = %d\n",i);
			tmp = meet_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		printf("word = %s\n",tmp);
	}
	printf("escape while\n");
	lst_tmp = head;
	printf("%s\n",lst_tmp->token);
	while(lst_tmp)
	{
		len += ft_strlen(lst_tmp->token);
		lst_tmp = lst_tmp->next;
	}
	printf("len = %d\n",len);
	result = ft_calloc(len + 1, sizeof(char));
	lst_tmp = head;
	tmp = result;
	while(lst_tmp)
	{
		i = 0;
		printf("lst_tmp->token = %s\n",lst_tmp->token);
		strcpy(tmp,lst_tmp->token);
		i += ft_strlen(lst_tmp->token);
		lst_tmp = lst_tmp->next;
		tmp += i;
	}
	printf("result  = %s\n",result);
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
		printf("%s\n",str);
		organize_quote(str);
		add_history(str);
		free(str);
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?
