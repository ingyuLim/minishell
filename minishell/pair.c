#include "minishell.h"

void	pair_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote && (ft_iswhitesp(str[i + 1]) || str[i + 1] == '\0'
				|| str[i + 1] == '|'))
		{
			str[i] = '\0';
			break ;
		}
		++i;
	}
}

char	*trim_quotes(char *str)
{
	int	i;
	int	sin_quote;
	int	dou_quote;

	i = 0;
	sin_quote = 0;
	dou_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dou_quote == 0 && sin_quote == 0)
			pair_quotes(str + i, '\'');
		if (str[i] == '\"' && dou_quote == 0 && sin_quote == 0)
			pair_quotes(str + i, '\"');
		++i;
	}
}
