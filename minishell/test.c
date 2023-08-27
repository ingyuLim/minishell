#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	char	**cmd;

	cmd = ft_split(argv[1], ' ');
	printf("%s\n",cmd[0]);
	printf("%s\n",cmd[1]);
	char *tmp = cmd[1];
	// while(*tmp)
	// {
	// 	printf("%c\n",*tmp);
	// 	tmp++;
	// }
	execve(cmd[0],cmd,envp);
}
//  /usr/bin/awk '{printf "1\n"}'
// ./a.out "/usr/bin/awk {printf\"1\n\"}"

// awk '{printf'1\n'}' => 안됨.
// /usr/bin/awk '{printf '1\n' }' => 되는데 개행이 안된다.... 왜지? 파싱이 어떻게 됐길래?