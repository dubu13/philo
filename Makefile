NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = main.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re