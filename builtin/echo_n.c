#include <unistd.h>
#include "../minishell/libft/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	if(*s1 == '\0' && *s2 == '\0')
		return (0);
	else
		return ((unsigned char) *s1 - (unsigned char) *s2);
}

void echo_n(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	if(ft_strcmp("-n",argv[1]) == 0)
	{
		i = 2;
		while(argv[i] != NULL)
		{
			ft_putstr_fd(argv[i], 1);
			if(argv[i + 1] != NULL)
				write(1," ",1);
			i++;
		}		
	}
	else
	{
		while(argv[i] != NULL)
		{
			ft_putstr_fd(argv[i], 1);
			if(argv[i + 1] != NULL)
				write(1," ",1);
			i++;
		}		
		write(1,"\n",1);
	}
}

int main(int argc, char *argv[])
{
	echo_n(argv);
	return 0;
}
