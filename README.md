# minishell

## Table of contents

- [minishell](#minishell)
	- [Table of contents](#table-of-contents)
	- [TODO](#todo)
	- [Analyzing a subject](#analyzing-a-subject)
	- [Mandatory](#mandatory)
	- [Bonus part](#bonus-part)
	- [Allow functions](#allow-functions)
		- [readline](#readline)
		- [rl\_clear\_history](#rl_clear_history)
		- [rl\_on\_new\_line](#rl_on_new_line)
		- [rl\_replace\_line](#rl_replace_line)
		- [rl\_redisplay](#rl_redisplay)
		- [add\_history](#add_history)
		- [printf](#printf)
		- [malloc](#malloc)
		- [free](#free)
		- [write](#write)
		- [access](#access)
		- [open](#open)
		- [read](#read)
		- [close](#close)
		- [fork](#fork)
		- [wait](#wait)
		- [waitpid](#waitpid)
		- [wait3](#wait3)
		- [wait4](#wait4)
		- [signal](#signal)
		- [sigaction](#sigaction)
		- [sigemptyset](#sigemptyset)
		- [sigaddset](#sigaddset)
		- [kill](#kill)
		- [exit](#exit)
		- [gextcwd](#gextcwd)
		- [chdir](#chdir)
		- [stat](#stat)
		- [lstat](#lstat)
		- [fstat](#fstat)
		- [unlink](#unlink)
		- [execve](#execve)
		- [dup](#dup)
		- [dup2](#dup2)
		- [pipe](#pipe)
		- [opendir](#opendir)
		- [readdir](#readdir)
		- [closedir](#closedir)
		- [strerror](#strerror)
		- [perror](#perror)
		- [isatty](#isatty)
		- [ttyname](#ttyname)
		- [ttyslot](#ttyslot)
		- [ioctl](#ioctl)
		- [getenv](#getenv)
		- [tcsetattr](#tcsetattr)
		- [tcgetattr](#tcgetattr)
		- [tgetent](#tgetent)
		- [tgetflag](#tgetflag)
		- [tgetnum](#tgetnum)
		- [tgetstr](#tgetstr)
		- [tgoto](#tgoto)
		- [tputs](#tputs)

## TODO

- [x] parsing
- [ ] syntax check
- [ ] execute
	- [ ] 다중 파이프
	- [ ] 환경 변수 변환?
	- [ ] awk 문법(파싱할 때 변수가 제일 많음)
- [ ] 환경 변수 출력하기

## Analyzing a subject

- [developing-linux-based-shell](https://www.geeksforgeeks.org/developing-linux-based-shell/)
- [bash-parser](https://vorpaljs.github.io/bash-parser-playground/)

## Mandatory

- 당신의 쉘은:
	- 새로운 명령어를 입력할 수 있는 `프롬프트`를 보여줘야 합니다 => readline
	- 작업 `히스토리`를 갖고 있어야 합니다. => add_history
	- (PATH 변수나 상대, 절대 경로를 활용하여) 올바른 실행 파일을 찾아 실행할 수 있어야 합니다. => parse, exceve
	- `전역변수`는 한 개 초과를 사용할 수 없으며, 왜 전역변수를 사용했는지 깊게 생각해 보고 그 이유를 설명할 수 있어야 합니다. => shell 종료 시?
	- 닫히지 않은 따옴표나 특정되지 않은 특수문자 (\\나 ; 등...) 을 해석하지 않아야 합니다.
	- ' (단일 따옴표) 안에 있는 메타문자를 해석하지 않아야 합니다.
	- " (이중 따옴표) 안에 있는 $ (달러 기호)를 제외한 메타문자를 해석하지 않아야 합니다.
- 다음의 리다이렉션을 구현해야 합니다:
	- `<`는 입력을 리다이렉션 하여야 합니다
	- `>`는 출력을 리다이렉션 하여야 합니다
	- `<<`에 구분 기호를 지정한 다음, 현재 소스에서 구분자를 포함한 줄을 만나기 전까지 입력값을 읽어들입니다. 기록을 업데이트할 필요는 없습니다! => open(RDONLY)
	- `>>`는 출력을 추가 모드로 리다이렉션합니다. => open(APPEND)
- `파이프`( `|` 문자)를 구현해야 합니다. 각 파이프라인마다 명령어의 출력값은 파이프로 연결되어 다음 명령어의 입력값으로 들어가야 합니다. => pipex
- `환경변수` (`$` 다음에 문자열이 오는 형식) 은 그들의 값으로 확장되어야 합니다.
- `$?`는 가장 최근에 실행한 포그라운드 파이프라인의 종료 상태를 확장하여야 합니다
- `ctrl-C`, `ctrl-D` 그리고 `ctrl-\` 는 bash와 동일하게 동작하여야 합니다.
- 상호작용이 가능할 때:
	- `ctrl-C`는 새로운 줄에 새로운 프롬프트를 출력합니다
	- `ctrl-D`는 쉘을 종료합니다.
	- `ctrl-\`은 아무런 동작도 하지 않습니다.
- 다음의 `내장 기능들`을 실행할 수 있어야 합니다:
	- `-n` 옵션을 사용할 수 있는 `echo`
	- 오직 상대 또는 절대경로만 사용하는 `cd` => chdir
	- 옵션이 없는 `pwd`
	- 옵션이 없는 `export`
	- 옵션이 없는 `unset`
	- 옵션이나 인자값이 없는 `env`
	- 옵션이 없는 `exit`
- `readline()` 함수는 메모리 누수를 일으킬 수 있습니다. 이를 고칠 필요는 없습니다. 하지만 `당신이 직접 작성한 코드는 메모리 누수를 일으킬 수 있다는 것을 의미합니다.`

> 💡 여러분은 과제의 설명에만 국한되도록 설계해야 합니다. 요구하지 않은 것들을 만드실 필요는 없습니다.<br>의문점이 생긴다면 [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)를 참고하세요.

## Bonus part

<br>

- 여러분의 프로그램은 다음을 구현해야 합니다:
	- 괄호를 이용해 우선순위를 표현한 `&&, ||`
	- 와일드카드 `*`가 현재 작업 디렉토리에 대해 동작하여야 합니다.

> 보너스는 필수로 구현해야 하는 파트가 완벽할 때만 평가될 것입니다. '완벽함' 이란, 모든 필수 파트가 전부 구현되어 있어야 하며 오작동하는 부분이 없어야 함을 의미합니다. 필수로 구현해야 하는 파트에서 만점을 받지 못한다면, 보너스 항목은 채점되지 않습니다.

## Allow functions

### readline

- [gnu](https://tiswww.case.edu/php/chet/readline/readline.html)
- [ref](https://wtg-study.tistory.com/103)
### rl_clear_history

> 히스토리 라이브러리의 clear_history() 함수와 동일한 방식으로 모든 항목을 삭제하여 히스토리 목록을 지웁니다. 이 함수는 clear_history와 다른 점은 Readline이 히스토리 목록에 저장하는 비공개 데이터를 해제한다는 점입니다.
### rl_on_new_line

> 일반적으로 줄 바꿈을 출력한 후 업데이트 함수에 새 (빈) 줄로 이동했음을 알립니다.
### rl_replace_line

> rl_line_buffer의 내용을 텍스트로 바꿉니다. 가능하면 포인트와 마크는 유지됩니다. clear_undo가 0이 아닌 경우 현재 줄과 연결된 실행 취소 목록이 지워집니다.
### rl_redisplay

> 0이 아닌 경우 이 포인터를 통해 간접적으로 Readline을 호출하여 편집 버퍼의 현재 콘텐츠로 디스플레이를 업데이트합니다. 기본적으로 이 값은 기본 Readline 재표시 함수인 rl_redisplay로 설정되어 있습니다(재표시 참조).

### add_history

- [ref](https://junselee.tistory.com/3)

### printf
### malloc
### free
### write
### access
### open
### read
### close
### fork
### wait
### waitpid
### wait3
### wait4
### signal

- [Ctrl + D, Ctrl + C 1](https://kldp.org/node/94835)
- [Ctrl + D, Ctrl + C 2](https://ohgyun.com/330)
### sigaction

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B2%98%EB%A6%AC-%ED%95%A8%EC%88%98-sigaction)
### sigemptyset

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A9-%EB%82%B4%EC%9A%A9%EC%9D%84-%EB%AA%A8%EB%91%90-%EC%82%AD%EC%A0%9C-%ED%95%A8%EC%88%98-sigemptyset)
### sigaddset

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A8%EC%97%90-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%B6%94%EA%B0%80-sigaddset)
### kill
### exit
### gextcwd

- [ref](https://www.it-note.kr/209)
- [ref](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bestheroz&logNo=116037413)
### chdir

- [ref](https://shaeod.tistory.com/325)
### stat

- [ref](https://www.it-note.kr/173)
### lstat

- [ref](https://reakwon.tistory.com/40)
### fstat

- [ref](https://www.it-note.kr/161)
### unlink
### execve
### dup
### dup2
### pipe
### opendir

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EC%97%B4%EA%B8%B0-%ED%95%A8%EC%88%98-opendir)
### readdir

- [ref](https://www.it-note.kr/14)
### closedir

- [ref](https://badayak.com/entry/C%EC%96%B8%EC%96%B4-%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EB%8B%AB%EA%B8%B0-closedir)
### strerror
### perror

- [ref](https://reakwon.tistory.com/214)
### isatty

- [ref](https://www.joinc.co.kr/w/man/3/isatty)
### ttyname

- [ref](https://www.joinc.co.kr/w/man/2/ttyname)
### ttyslot

- [man](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
### ioctl

- [ref](https://jeongzero.oopy.io/8d9187bc-63c8-4ed1-8bbc-653c16584249)
### getenv

- [ref](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=hoon2huny&logNo=50005636846)
### tcsetattr
### tcgetattr
### tgetent
### tgetflag
### tgetnum
### tgetstr
### tgoto
### tputs
