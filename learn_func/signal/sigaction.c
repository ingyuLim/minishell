// https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B2%98%EB%A6%AC-%ED%95%A8%EC%88%98-sigaction

/* #include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction act_new;
struct sigaction act_old;

void sigint_handler( int signo)
{
	(void) signo;
	printf( "Ctrl-C 키를 눌루셨죠!!\n");
	printf( "또 누르시면 종료됩니다.\n");
	sigaction( SIGINT, &act_old, NULL);
}

int main( void)
{

	act_new.sa_handler = sigint_handler; // 시그널 핸들러 지정
	sigemptyset( &act_new.sa_mask);		// 시그널 처리 중 블록될 시그널은 없음

	// SIGINT를 지정하면서 act_old에 이전 정보를 구합니다.
	sigaction( SIGINT, &act_new, &act_old);
	while( 1 ){
	  printf( "badayak.com\n");
	  sleep( 1);
	}
} */

/* #include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler( int signo)
{
	(void) signo;
	int	ndx;

	printf( "Ctrl-C 키를 누르셨죠.\n");
	printf( "3초간 대기하겠습니다. 이때 Ctrl-Z키를 눌러 주세요.\n");

	for ( ndx = 3; 0 < ndx; ndx--){
		printf( "%d 초 남았습니다.\n", ndx);
		sleep( 1);
	}
}

int main( void)
{
	struct sigaction act;

	act.sa_handler = sigint_handler;  // 시그널 핸들러 지정
	sigfillset( &act.sa_mask);		  // 모든 시그널을 블록

	sigaction( SIGINT, &act, NULL);
	while(1 ){
		printf( "badyak.com\n");
		sleep( 1);
	}
} */

// https://www.joinc.co.kr/w/man/2/sigaction

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void sig_int(int signo);
void sig_usr(int signo);

int main()
{
	int i = 0;
	struct sigaction intsig, usrsig;

	usrsig.sa_handler = sig_usr;
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;

	intsig.sa_handler = sig_int;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;

	// SIGINT에 대해서 sig_int를 등록한다.
	if (sigaction(SIGINT, &intsig, 0) == -1)
	{
		printf ("signal(SIGINT) error");
		return -1;
	}

	// SIGUSR2에 대해서 usrsig를 등록한다.
	if (sigaction(SIGUSR2, &usrsig, 0) == -1)
	{
		printf ("signal(SIGUSR2) error");
		return -1;
	}

	while(1)
	{
		printf("%d\n", i);
		i++;
		sleep(1);
	}
}

void sig_int(int signo)
{
	sigset_t sigset, oldset;

	// 핸들러가 수행되는 동안 수신되는 모든 시그널에 대해서
	// 블럭한다.
	sigfillset(&sigset);
	if (sigprocmask(SIG_BLOCK, &sigset, &oldset) < 0)
	{
		printf("sigprocmask %d error \n", signo);
	}
	fprintf(stderr, "SIGINT !!!!\n");
	sleep(5);
}

void sig_usr(int signo)
{
	(void) signo;
	printf("sig_usr2\n");
}
