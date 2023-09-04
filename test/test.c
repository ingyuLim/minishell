#include "../minishell/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	char	**cmd;

	cmd = ft_split(argv[1], ' ');
	printf("%s\n",cmd[0]);
	cmd[1] = "\a";
	printf("%s\n",cmd[1]);
	printf("%d\n",cmd[1][0]);
	// char *tmp = cmd[1];
	// while(*tmp)
	// {
	// 	printf("%c\n",*tmp);
	// 	tmp++;
	// }
	execve(cmd[0],cmd,envp);
	printf("fail\n");
}

//  /usr/bin/awk '{printf "1\n"}'
// ./a.out "/usr/bin/awk {printf\"1\n\"}"

// awk '{printf'1\n'}' => 안됨.
// /usr/bin/awk '{printf '1\n' }' => 되는데 개행이 안된다.... 왜지? 파싱이 어떻게 됐길래? => printf 뒤 작은 따옴표는 변수로 인식 되는데 숫자의 경우 atoi처럼 짤라준다.

// /bin/echo \a => a 출력. ('\'이 전달이 안되는 듯.) => '\' 다음 특수 문자가 아니면 그냥 삭제.
// /bin/echo '\a' => \a 출력. => 작은 따옴표로 묶이면 몽땅 문자로 취급. flag로 on off하기.
// 큰 따옴표와 작은 따옴표 차이? 

// "gre"p" "a""
// "gre"p"" "a" 스페이스 기준으로 해서 따옴표 짝 찾으면 현재까지의 따옴표가 홀짝인지 보고 짝수면 하나의 묶음으로 보고 홀수면 아직 짝을 못찾았으니 더 간다.