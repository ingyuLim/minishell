#include "minishell.h"

void	exit_with_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int ft_issymbol(char c)
{
	return(c == '|' || c == '<' || c == '>' || c== ';');
}

int ft_isseparator(char c)
{
	return(ft_iswhitespace(c) || ft_issymbol(c) || c == '\0');
}

int ft_isword(char c)
{
	return(!ft_iswhitespace(c) && !ft_issymbol(c) && c != '\0');
}

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
	*i = last + 1;
	return result;
}

char *make_word(char *str, int *i)
{
	int		last;
	char	*end;
	char	*tmp;
	char	*result;

	result = ft_calloc(1, sizeof(char));
	last = *i;
	while(!ft_isseparator(str[last]))
	{
		if (ft_isquote(str[last]))
			end = meet_quote(str, &last, str[last]);
		else
			end = meet_sep(str, &last);
		if (end != NULL)
		{
			tmp = result;
			result = ft_strjoin(result,end);
			free(tmp);
			free(end);
		}
	}
	*i = last;
	return (result);
}

char *make_symbol(char *str, int *i)
{
	char	*result;
	int		len;

	len = 1;
	while(ft_issymbol(str[*i + len]))
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
		if(ft_issymbol(str[i])) // '|' '<' '>' ';' 일 경우
		{
			tmp = make_symbol(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else if(ft_isword(str[i])) // '|' '<' '>' ';', whitespace가 아닐 경우 => "이거나 '이거나 문자일 경우
		{
			tmp = make_word(str, &i);
			ft_lstadd_back(&head, ft_lstnew(tmp));
		}
		else // whitespace일 경우
			i++;
	}
	return (head);
}

char	*testcase[100] =
{
	"ls",									// ls
	"\'ls\'",								// 'ls'
	"\"ls\"",								// "ls"
	"\'l\'\'s\'",							// 'l''s'
	"\'l\"\"s\'",							// 'l""s'
	"\'l\'\'\'\'\'\'\'\'s\'",				// 'l''''''''s'
	"\"l\"\"\"\"\"\"\"\"s\"",				// "l""""""s"
	"ls -a",								// ls -a
	"\"ls -a\"",							// "ls -a"
	"\"\"gre\"p\" \"a\"",					// ""gre"p" "a"
	"\"gr\"ep\" a\"",						// "gr"ep" a"
	"ls|grep a",							// ls|grep a
	"ls| grep a",							// ls| grep a
	"ls |grep a",							// ls |grep a
	"ls | grep a",							// ls | grep a
	"\'l\'\'\'\'\'\'s\'|grep\"\" \"a\"",	// 'l''''''s'|grep"" "a"
	"\'ls\'|\"grep\" \"a\"",				// 'ls'|"grep" "a"
	NULL
};

void	print(t_list *lst)
{
	int	cnt = 0;

	printf("\033[1;37m");
	while (lst != NULL)
	{
		printf("%d: %s\n", cnt, lst->token);
		lst = lst->next;
		++cnt;
	}
	printf("\033[1;30m");
	printf("\ndivided into %d tokens\n", cnt);
	printf("\033[0m");
}

void	leak(void)
{
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}

int	main(void)
{
	atexit(leak);
	t_list	*tmp;

	for (size_t i = 0; testcase[i] != NULL; i++)
	{
		if (!(9 <= i && i <= 15))
			continue ;
		printf("\033[1;32m"); // green
		printf("=================================\n");
		printf("\t  Test Case #%zu\n", i);
		printf("=================================\n\n");
		printf("\033[0m");

		printf("\033[1;31m");
		printf("Input String:\n");
		printf("\033[0m");

		printf("\033[1;37m");
		printf("%s\n\n", testcase[i]);
		printf("\033[0m");

		printf("\033[1;31m");
		printf("Your Parse Function Result:\n");
		printf("\033[0m");

		tmp = tokenize(testcase[i]);
		print(tmp);
		ft_lstclear(&tmp, free);

		usleep(700000);
	}
	return (0);
}
