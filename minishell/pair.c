#include "minishell.h"

char	*single_quotes(char **str, int *sin_quote)
{
	char	*tmp;

	while (**str != '\0')
	{
		/* code */
	}

}

char	*trim_quotes(char *str)
{
	t_list	*head;
	int		quote[2];

	head = ft_lstnew(0);
	quote[SINGLE] = 0;
	quote[DOUBLE] = 0;
	while (*str)
	{
		if (*str == '\'' && quote[SINGLE] == 0 && quote[DOUBLE] == 0)
		{
			quote[SINGLE] = 1;
			double_quotes(str);
			quote[SINGLE] = 0;
		}
		if (*str == '\"' && quote[SINGLE] == 0 && quote[DOUBLE] == 0)
		{
			quote[DOUBLE] = 1;
			single_quotes(&str, &quote[DOUBLE]);
			quote[DOUBLE] = 0;
		}
		str++;
	}
}
