NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -pthread

SRCS = src/main.c src/simulation.c src/parsing.c src/init.c src/cleanup.c \
	src/actions.c src/monitor.c src/time.c src/state.c src/print.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	 rm -f $(OBJS)

fclean: clean
	 rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
