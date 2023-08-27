#include "minishell.h"

void	split_by_pipe(char *str)
{
	/* 1. */char **arr = ft_split(str,'|');
	char **tmp;
	int n = 1;
	while(arr[n-1])
		n++;
	// printf("n = %d\n",n);
	char ***result = (char ***)malloc(sizeof(char **) * n);
	int i = 0;
	int j = 0;
	while(i < n - 1)
	{
		// printf("arr[i] = %s\n",arr[i]);
		result[i] = ft_split(arr[i],' ');
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

int main(void)
{
	split_by_pipe("\"\"\"l\"\"s\"\" | grep \"a\" | gre\"p\" e ");
}
// ""l""s"" | grep "a" | gre"p" e 
// -> "ls" -> "grep a"
// ""ls"" -> grep "a" |         
// -> "ls" -> grep -> a
// grep e