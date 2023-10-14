.SUFFIXES : .c .o

NAME=minishell
CC=cc
PRINTF=printf
CFLAGS=-Werror -Wall -Wextra
LIBFT=./libft/libft.a
LLDB=-g
DEBUG=-g3 -fsanitize=address

SRCS= main.c \
	utils.c \
	error.c \
	signal.c \
	parse/parse.c \
	parse/env_vars.c \
	parse/env_utils.c \
	parse/env_join.c \
	syntax/syntax.c \
	syntax/syntax_utils.c \
	execute/change_in_and_out.c \
	execute/connect_pipe.c \
	execute/execute_builtin.c \
	execute/execute_cnt.c \
	execute/execute_heredoc.c \
	execute/execute_redir.c \
	execute/execute_utils1.c \
	execute/execute_utils2.c \
	execute/execute.c \
	execute/use_function1.c \
	execute/use_function2.c \
	builtin/builtin_utils.c \
	builtin/cd.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/exit.c \
	builtin/export.c \
	builtin/pwd.c \
	builtin/unset.c
OBJS=$(SRCS:.c=.o)

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

ASCII_ART="\
.........................................................................\n\
.\#\#...\#\#..\#\#\#\#\#\#..\#\#...\#\#..\#\#\#\#\#\#...\#\#\#\#...\#\#..\#\#..\#\#\#\#\#\#..\#\#......\#\#.....\n\
.\#\#\#.\#\#\#....\#\#....\#\#\#..\#\#....\#\#....\#\#......\#\#..\#\#..\#\#......\#\#......\#\#.....\n\
.\#\#.\#.\#\#....\#\#....\#\#.\#.\#\#....\#\#.....\#\#\#\#...\#\#\#\#\#\#..\#\#\#\#....\#\#......\#\#.....\n\
.\#\#...\#\#....\#\#....\#\#..\#\#\#....\#\#........\#\#..\#\#..\#\#..\#\#......\#\#......\#\#.....\n\
.\#\#...\#\#..\#\#\#\#\#\#..\#\#...\#\#..\#\#\#\#\#\#...\#\#\#\#...\#\#..\#\#..\#\#\#\#\#\#..\#\#\#\#\#\#..\#\#\#\#\#\#.\n\
.........................................................................\
"

all: clear $(NAME)

clear:
	clear
	@echo "$(CYAN)"
	@echo $(ASCII_ART)
	@echo "$(DEFAULT)"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(LIBFT):
	$(MAKE) bonus -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	$(MAKE) debug -C ./libft
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"

lldb:
	$(MAKE) lldb -C ./libft
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(LLDB)"

.PHONY: all clean fclean re debug lldb
