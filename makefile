NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = coder.c main.c parsing.c queue_pull.c queue_push.c queue_utlis.c threading_main.c threading_utlis.c threading.c utlis.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# valgrind-mem: $(NAME)
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) $(ARGS)
# 
# valgrind-thread: $(NAME)
# 	valgrind --tool=helgrind -s ./$(NAME) $(ARGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind-mem valgrind-thread