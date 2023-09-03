#include "minishell.h"

int is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*gnl_strndup(char *src, unsigned int n)
{
	char			*dup;
	unsigned int	dup_idx;

	dup = (char *)ft_calloc(n + 1 , sizeof(char));
	if (!dup)
		return (NULL);
	dup_idx = 0;
	while (dup_idx < n)
	{
		dup[dup_idx] = src[dup_idx];
		dup_idx++;
	}
	return (dup);
}

int	even(int n)
{
	if (n%2 == 0)
		return 1;
	else
		return FALSE;
}

char *ws_pass(char *str)
{
	while(ft_iswhitesp(*str))
		str++;
	return str;
}
	
char *meet_quote(char *str, int *i, char quote) //띄어쓰기까지 모두 문자 취급
{
	int idx = *i;
	int len = 0;
	char *result;

	idx++;
	while(str[idx++] != quote)
		len++;
	result = gnl_strndup(str + (*i), len);
	*i = idx;
	return result;
}

char *meet_char(char *str)
{
	int i = 0;
	int len = 0;
	char *result;

	while(!(ft_iswhitesp(str[i]) || is_quote(str[i]) || str[i]))
	{
		i++;
		len++;
	}
	result = gnl_strndup(str, len);
	return result;
}

void ft_strcpy(char *src, char *dst)
{
	while(*src)
		*dst = *src;
}

char	*organize_quote(char *str)
{
	t_list	*head;
	t_list	*lst_tmp;
	int len = 0;
	char	*tmp;
	int i = 0;
	char *result;

	//일단은 쪼개서 합치는 방식.
	while(str[i])
	{
		while(ft_iswhitesp(str[i]))
			i++;
		if(is_quote(str[i]))
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
	lst_tmp = head;
	while(lst_tmp)
	{
		len += ft_strlen(lst_tmp->token);
		lst_tmp = lst_tmp->next;
	}
	result = ft_calloc(len + 1, sizeof(char));
	lst_tmp = head;
	i = 0;
	while(lst_tmp)
	{
		ft_strcpy(lst_tmp->token,result);
		i += ft_strlen(lst_tmp->token);
		lst_tmp = lst_tmp->next;
		result += i;
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
		// tokenize(str);
		// make_token();
		// printf("head : %llu\n",head);
		add_history(str);
		free(str);  
	}
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?