.SUFFIXES : .c .o

NAME=minishell
CC=gcc
PRINTF = printf
CFLAGS= -Werror -Wall -Wextra -I/opt/homebrew/opt/readline/include
LIBFT=./libft/libft.a
LLDB= -g
DEBUG= -g3 -fsanitize=address

SRCS= main.c \
	utils.c \
	error.c \
	test/test.c \
	signal.c \
	$(wildcard ./syntax/*.c) \
	$(wildcard ./execute/*.c) \
	$(wildcard ./builtin/*.c) \
	$(wildcard ./parse/*.c)
TEST_SRCS= $(wildcard ./test/*.c) \
	utils.c \
	error.c \
	signal.c \
	$(wildcard ./syntax/*.c) \
	$(wildcard ./execute/*.c) \
	$(wildcard ./builtin/*.c) \
	$(wildcard ./parse/*.c)
OBJS=$(SRCS:.c=.o)
TEST_OBJS=$(TEST_SRCS:.c=.o)

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L/opt/homebrew/opt/readline/lib -lreadline -o $(NAME)
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

test:
	$(MAKE) 'OBJS=$(TEST_OBJS)' all

.PHONY: all clean fclean re debug lldb test
