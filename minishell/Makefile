.SUFFIXES : .c .o

NAME=minishell
CC=gcc
CFLAGS=-Wall -Werror -Wextra
LIBFT=./libft/libft.a
DEBUG=-g3 -fsanitize=address

SRCS=\
	main.c \
	parse.c \
	syntax.c \
	utils.c \
	error.c \
	execute.c \
	seunan/cd.c \
	seunan/pwd.c \
	seunan/echo.c
TEST_SRCS=\
	test_parse.c \
	syntax.c \
	parse.c \
	error.c \
	utils.c
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
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"

test:
	$(MAKE) 'OBJS=$(TEST_OBJS)' all

.PHONY: all clean fclean re debug test
