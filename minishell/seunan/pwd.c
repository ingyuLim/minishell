#include "../minishell.h"

void	pwd(void)
{
	char *path;

	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	free(path);
}
