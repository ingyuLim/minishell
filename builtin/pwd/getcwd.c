// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bestheroz&logNo=116037413

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void	leak(void)
{
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}

int main(void)
{
	atexit(leak);
	char *cwd;
	char wd[BUFSIZ];

	cwd = getcwd(NULL, BUFSIZ);
	free(cwd);
	printf("1.Current Directory : %s\n", cwd);
	chdir("TEST/");
	getcwd(wd, BUFSIZ);
	printf("2.Current Directory : %s\n", wd);
	return 0;

}
