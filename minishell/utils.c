#include "minishell.h"

// 에러 메시지 출력 후 프로그램 종료
void	exit_with_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// | < > 에 해당하는 문자인지 확인
int ft_issymbol(char c)
{
	return(c == '|' || c == '<' || c == '>' );
}

// 구분자(공백, | < >, '\0')인지 확인
int ft_isseparator(char c)
{
	return(ft_iswhitespace(c) || ft_issymbol(c) || c == '\0');
}

// 구분자(공백, | < >, '\0')가 아닌 문자인지 확인
int ft_isword(char c)
{
	return(!ft_iswhitespace(c) && !ft_issymbol(c) && c != '\0');
}
