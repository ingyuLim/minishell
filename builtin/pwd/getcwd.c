// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bestheroz&logNo=116037413

#include<stdio.h>
#include<unistd.h>

int main(void)
{
	char *cwd;
	char wd[BUFSIZ];

	cwd = getcwd(NULL, BUFSIZ);
	printf("1.Current Directory : %s\n", cwd);
	chdir("TEST/");
	getcwd(wd, BUFSIZ);
	printf("2.Current Directory : %s\n", wd);
	return 0;

}
