NAME =	philo

CC =	gcc

SRC = philo.c helpers.c

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

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
	norminette *.c
	norminette *.h

.phony:
	all clean fclean re norm