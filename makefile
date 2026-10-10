NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = coder.c main.c parsing.c queue_pull.c queue_push.c queue_utlis.c threading_main.c threading_utlis.c threading.c utlis.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(NAME) 1 300 100 100 100 3 10 edf

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) 5  1200  5  100  30  1  3  fifo

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re