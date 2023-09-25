.SUFFIXES : .c .o

NAME=minishell
CC=gcc
CFLAGS=-Wall -Werror -Wextra
LIBFT=./libft/libft.a
LLDB= -g
DEBUG= -g3 -fsanitize=address

SRCS= main.c \
	minishell.c \
	utils.c \
	error.c \
	test/test.c \
	$(wildcard ./syntax/*.c) \
	$(wildcard ./execute/*.c) \
	$(wildcard ./builtin/*.c) \
	$(wildcard ./parse/*.c)
TEST_SRCS= ./test/test_parse.c \
	minishell.c \
	utils.c \
	error.c \
	$(wildcard ./syntax/*.c) \
	$(wildcard ./execute/*.c) \
	$(wildcard ./builtin/*.c) \
	$(wildcard ./parse/*.c)
OBJS=$(SRCS:.c=.o)
TEST_OBJS=$(TEST_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	$(MAKE) clean
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
