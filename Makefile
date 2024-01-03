.SUFFIXES : .c .o

NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Werror -Wextra
MEMORT  := -fsanitize=address
LLDB    := -g
LIBFT   := ./libft/libft.a

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m
WHITE   := \033[37m
RESET   := \033[0m

INCLUDE := -I./inc -I./libft/inc
SRC_DIR := ./src

MACOS_INCLUDE := -I/opt/homebrew/opt/readline/include
MACOS_LIBRARY := -lreadline

SRC    := \
		main.c \
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
OBJ    := $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

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

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBFT) $(MACOS_LIBRARY) -o $(NAME)
	@printf "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(LIBFT):
	$(MAKE) bonus -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJ) 

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

macos:
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(MACOS_INCLUDE)"

.PHONY: all clean fclean re debug lldb macos
