# minishell

## readline

- [ref](https://wtg-study.tistory.com/103)
- [gnu](https://tiswww.case.edu/php/chet/readline/readline.html)
## rl_clear_history

> 히스토리 라이브러리의 clear_history() 함수와 동일한 방식으로 모든 항목을 삭제하여 히스토리 목록을 지웁니다. 이 함수는 clear_history와 다른 점은 Readline이 히스토리 목록에 저장하는 비공개 데이터를 해제한다는 점입니다.
## rl_on_new_line

> 일반적으로 줄 바꿈을 출력한 후 업데이트 함수에 새 (빈) 줄로 이동했음을 알립니다.
## rl_replace_line

> rl_line_buffer의 내용을 텍스트로 바꿉니다. 가능하면 포인트와 마크는 유지됩니다. clear_undo가 0이 아닌 경우 현재 줄과 연결된 실행 취소 목록이 지워집니다.
## rl_redisplay

> 0이 아닌 경우 이 포인터를 통해 간접적으로 Readline을 호출하여 편집 버퍼의 현재 콘텐츠로 디스플레이를 업데이트합니다. 기본적으로 이 값은 기본 Readline 재표시 함수인 rl_redisplay로 설정되어 있습니다(재표시 참조).

## add_history

- [ref](https://junselee.tistory.com/3)

## printf
## malloc
## free
## write
## access
## open
## read
## close
## fork
## wait
## waitpid
## wait3
## wait4
## signal
## sigaction

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B2%98%EB%A6%AC-%ED%95%A8%EC%88%98-sigaction)
## sigemptyset

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A9-%EB%82%B4%EC%9A%A9%EC%9D%84-%EB%AA%A8%EB%91%90-%EC%82%AD%EC%A0%9C-%ED%95%A8%EC%88%98-sigemptyset)
## sigaddset

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A8%EC%97%90-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B6%94%EA%B0%80-sigaddset)
## kill
## exit
## gextcwd

- [ref](https://www.it-note.kr/209)
- [ref](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bestheroz&logNo=116037413)
## chdir

- [ref](https://shaeod.tistory.com/325)
## stat

- [ref](https://www.it-note.kr/173)
## lstat

- [ref](https://reakwon.tistory.com/40)
## fstat

- [ref](https://www.it-note.kr/161)
## unlink
## execve
## dup
## dup2
## pipe
## opendir

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EC%97%B4%EA%B8%B0-%ED%95%A8%EC%88%98-opendir)
## readdir

- [ref](https://www.it-note.kr/14)
## closedir

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EB%8B%AB%EA%B8%B0-closedir)
## strerror
## perror

- [ref](https://reakwon.tistory.com/214)
## isatty

- [ref](https://www.joinc.co.kr/w/man/3/isatty)
## ttyname

- [ref](https://www.joinc.co.kr/w/man/2/ttyname)
## ttyslot

- [man](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
## ioctl

- [ref](https://jeongzero.oopy.io/8d9187bc-63c8-4ed1-8bbc-653c16584249)
## getenv

- [ref](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=hoon2huny&logNo=50005636846)
## tcsetattr
## tcgetattr
## tgetent
## tgetflag
## tgetnum
## tgetstr
## tgoto
## tputs
