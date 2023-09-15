// https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A8%EC%97%90-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B6%94%EA%B0%80-sigaddset

#include <stdio.h>
#include <signal.h>

int main( void)
{
   sigset_t set;

   sigemptyset( &set);        // 시그널 집합 변수의 내용을 모두 제거합니다.
   sigaddset( &set, SIGINT);  // 시그널 집합 변수에 SIGINT를 추가합니다.

   // SIGINT 가 등록되었는지 확인합니다.

   switch( sigismember( &set, SIGINT)){
   case 1   :  printf( "SIGINT는 포함되어 있습니다.\n");
               break;
   case 0   :  printf( "SIGINT는 없습니다.\n");
               break;
   default  :  printf( "sigismember() 호출에 실패했습니다.\n");
   }

   // SIGSYS 가 등록되었는지 확인합니다.

   switch( sigismember( &set, SIGSYS)){
   case 1   :  printf( "SIGSYS는 포함되어 있습니다.\n");
               break;
   case 0   :  printf( "SIGSYS는 없습니다.\n");
               break;
   default  :  printf( "sigismember() 호출에 실패했습니다.\n");
   }

   return 0;
}
