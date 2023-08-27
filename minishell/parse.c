#include "minishell.h"

void	split_by_pipe(char *str)
{
	char	**arr;
	int		len;
	int		i;
	int		j;

	arr = ft_split(str,'|');
	len = 0;
	while (arr[len] != NULL)
		++len;
	char ***result = (char ***)malloc(sizeof(char **) * len + 1);
	i = 0;
	while(i < len)
	{
		result[i] = ft_split(arr[i], ' ');
		i++;
	}
	i = 0;
	while(result[i])
	{
		j = 0;
		while(result[i][j])
		{
			printf("%s ",result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// ""l""s"" | grep "a" | gre"p" e
// -> "ls" -> "grep a"
// ""ls"" -> grep "a" |
// -> "ls" -> grep -> a
// grep e
