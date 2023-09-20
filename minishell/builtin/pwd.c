#include "../minishell.h"

int	b_pwd(void)
{
	char *path;

	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	free(path);
	return (0);
}
