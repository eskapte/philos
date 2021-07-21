NAME =	philo

CC =	gcc

SRC = philo.c helpers.c actions.c time_helpers.c watcher.c

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -g -O2

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make

norm:
	python3 -m norminette *.c
	python3 -m norminette *.h

.phony:
	all clean fclean re norm