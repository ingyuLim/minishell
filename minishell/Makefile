.SUFFIXES : .c .o

NAME=minishell
CC=gcc
CFLAGS=-Wall -Werror -Wextra
LIBFT=./libft/libft.a
DEBUG=-g3 -fsanitize=address

SRCS=main.c seunan_parse.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C ./libft
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME) $(BONUS)

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	$(MAKE) fclean
	$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"

.PHONY: all clean fclean re debug
