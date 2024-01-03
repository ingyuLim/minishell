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

all: $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

clear:
	clear
	@echo "$(CYAN)"
	@echo $(ASCII_ART)
	@echo "$(DEFAULT)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(WHITE)Creating $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBFT) $(MACOS_LIBRARY) -o $(NAME)

$(LIBFT):
	@$(MAKE) bonus -C ./libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(CYAN)Compiled:$(RESET) $< -> $@"

clean:
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJ) 
	@echo "$(BLUE)Cleaned up object files$(RESET)"

fclean: clean
	@rm -f $(NAME) $(LIBFT)
	@echo "$(BLUE)Cleaned up executable and library$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

mem:
	@$(MAKE) fclean
	@$(MAKE) mem -C ./libft
	@$(MAKE) all CFLAGS="$(CFLAGS) $(MEMORY)"
	@echo "$(YELLOW)Executable compiled with memory sanitizer$(RESET)"

lldb:
	@$(MAKE) fclean
	@$(MAKE) lldb -C ./libft
	@$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"
	@echo "$(YELLOW)Executable compiled to enable LLDB debugging$(RESET)"


.PHONY: all clean fclean re debug lldb
