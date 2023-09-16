#include "../minishell.h"

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, BUFSIZ));
}
