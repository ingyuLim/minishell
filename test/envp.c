#include "minishell.h"

char *daller_str(char *str, char *envp[]) //str = "$~~~~~"
{
	char *result;
	char *tmp;
	int i = 0;
	int str_len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * str_len +1);
	str++;
	while(str != NULL && *str)
	{
		tmp[i] = *str;
		str++;
		i++;
	}
	tmp[i] = '=';
	while (*envp) 
	{
		if (ft_strncmp(tmp, *envp, str_len) == 0)
		{
			free(tmp);
			return (ft_strdup((*envp) + str_len));
		}
		else
			envp++;
	}
	free(tmp);
	return (NULL);
}


void to_lowercase(char *str)
{
	while(*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

int main(int argc, char **argv, char **envp)
{
	printf("%s\n",daller_str("$PATH",envp));
	char str[] = "ABcdEFg";
	to_lowercase(str);;
	printf("%s\n", str);
	return 0;
}
