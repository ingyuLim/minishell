#include "../minishell.h"

/* TEST */
static char	test_state[8][20] = {
	"START",				// 명령어의 시작
	"CMD",
	"FNAME",
	"PIPE",					// |
	"IN_REDIR",				// <
	"OUT_REDIR",			// >
	"HEREDOC",				// << limiter
	"PAIR_OUT_REDIR",		// >>
};

void	leak(void)
{
	system("leaks --list minishell");
}

void	print_tokens(t_list *lst)
{
	int	cnt = 0;

	printf("\033[1;37m");
	while (lst != NULL)
	{
		printf("%d: %s\nstate: %s\n", cnt, lst->token, test_state[lst->state]);
		lst = lst->next;
		++cnt;
	}
	printf("\033[1;30m");
	printf("\ndivided into %d tokens\n", cnt);
	printf("\033[0m");
}
