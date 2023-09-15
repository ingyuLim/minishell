// https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A9-%EB%82%B4%EC%9A%A9%EC%9D%84-%EB%AA%A8%EB%91%90-%EC%82%AD%EC%A0%9C-%ED%95%A8%EC%88%98-sigemptyset

#include <stdio.h>
#include <signal.h>

int main( void)
{
	sigset_t set;

	sigemptyset( &set);			// 시그널 집합 변수의 내용을 모두 제거합니다.
	sigaddset( &set, SIGINT);	// 시그널 집합 변수에 SIGINT를 추가합니다.

	// SIGINT 가 등록되었는지 확인합니다.

	switch( sigismember( &set, SIGINT)){
	case 1	:  printf( "SIGINT는 포함되어 있습니다.\n");
					break;
	case 0	:  printf( "SIGINT는 없습니다.\n");
					break;
	default  :  printf( "sigismember() 호출에 실패했습니다.\n");
	}

	// SIGSYS 가 등록되었는지 확인합니다.

	switch( sigismember( &set, SIGSYS)){
	case 1	:  printf( "SIGSYS는 포함되어 있습니다.\n");
					break;
	case 0	:  printf( "SIGSYS는 없습니다.\n");
					break;
	default  :  printf( "sigismember() 호출에 실패했습니다.\n");
	}

	return 0;
}
