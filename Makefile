NAME = minishell

SRCS = main.c \
		handler.c \
		create_token.c \
		parser.c \

OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft ft_printf clean fclean re
