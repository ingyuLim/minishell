.SUFFIXES : .c .o

NAME=minishell
CC=gcc
CFLAGS=-Wall -Werror -Wextra
LIBFT=./libft/libft.a
DEBUG=-g3 -fsanitize=address

SRCS=main.c deque.c cmd_push.c cmd_swap.c cmd_rotate.c parse.c set_idx.c sort.c utils.c find_min_rot.c find_min_rot_utils.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
