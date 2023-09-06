#include "minishell.h"

char	*test[100] =
{
	"ls",									// ls
	"\'ls\'",								// 'ls'
	"\"ls\"",								// "ls"
	"\'l\'s\'",								// 'l's'
	"\'l\'\'s\'",							// 'l''s'
	"\'l\'\'\'\'\'\'\'\'s\'",				// 'l''''''''s'
	"\"l\"\"\"\"\"\"\"\"s\"",				// "l""""""s"
	"ls -a",								// ls -a
	"\"ls -a\"",							// "ls -a"
	"\"\"gre\"p\" \"a\"",					// ""gre"p" "a"
	"\"gr\"ep\" a\"",						// "gr"ep" a"
	"ls|grep a",							// ls|grep a
	"ls| grep a",							// ls| grep a
	"ls |grep a",							// ls |grep a
	"ls | grep a",							// ls | grep a
	"\'l\'\'\'\'\'\'s\'|grep\"\" \"a\"",	// 'l''''''s'|grep"" "a"
	"\'ls\'|\"grep\" \"a\"",				// 'ls'|"grep" "a"
	NULL
};

void	print(t_list *lst)
{
	int	cnt = 0;

	printf("\033[1;37m");
	while (lst != NULL)
	{
		printf("%d: %s\n", cnt, lst->token);
		lst = lst->next;
		++cnt;
	}
	printf("\033[1;30m");
	printf("\ndivided into %d tokens\n", cnt);
	printf("\033[0m");
}

int	main(void)
{

	for (size_t i = 0; test[i] != NULL; i++)
	{
		printf("\033[1;32m"); // green
		printf("=================================\n");
		printf("\t  Test Case #%zu\n", i);
		printf("=================================\n\n");
		printf("\033[0m");

		printf("\033[1;31m");
		printf("Input String:\n");
		printf("\033[0m");

		printf("\033[1;37m");
		printf("%s\n\n", test[i]);
		printf("\033[0m");

		printf("\033[1;31m");
		printf("Your Parse Function Result:\n");
		printf("\033[0m");

		print(parse(test[i]));

		usleep(700000);
	}
	return (0);
}
