#include "../minishell.h"

int	b_pwd(void)
{
	char	*path;

	path = getcwd(NULL, BUFSIZ);
	ft_putendl_fd(path, STDOUT_FILENO);
	use_free(path);
	return (0);
}
