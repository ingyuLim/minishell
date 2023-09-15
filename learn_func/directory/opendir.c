// https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EC%97%B4%EA%B8%B0-%ED%95%A8%EC%88%98-opendir

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main()
{
	DIR				*dir_info;
	struct dirent  *dir_entry;

	mkdir("test_A", 0755);		// 실행 파일이 있는 곳에 생성
	mkdir("test_B", 0755);		// 실행 파일이 있는 곳에 생성

	dir_info = opendir(".");	// 현재 디렉토리를 열기
	if (dir_info != NULL)
	{
		while ((dir_entry = readdir(dir_info)) != NULL)
			printf("%s\n", dir_entry->d_name); // 디렉토리 안에 있는 모든 파일과 디렉토리 출력
		closedir( dir_info);
	}

	return (0);
}
