NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread

SRCS = src/main.c \
	src/parsing/parsing.c \
	src/init/init.c src/init/cleanup.c \
	src/execution/simulation.c src/execution/actions.c src/execution/monitor.c \
	src/utils/time.c src/utils/state.c src/utils/print.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c include/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	 rm -f $(OBJS)

fclean: clean
	 rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
