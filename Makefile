NAME = philo
CC = cc -Wall -Wextra -Werror
CFLAGS = -Iincludes/
SDIR = src/
SRC = $(SDIR)main.c $(SDIR)err.c $(SDIR)libc_utils.c $(SDIR)time.c $(SDIR)philo_utils.c $(SDIR)fork_utils.c
OBJS = $(SRC:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
