NAME = minishell

SRCS = main.c \
		handler.c \
		create_token.c \
		parser.c \
		split.c \
		list.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

INC = -Ilibft -Llibft -lft 

LIBFT = libft/libft.a

CC = cc -g -Wall -Wextra -Werror

all: $(NAME)

$(LIBFT):
	cd libft && $(MAKE)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)
	cd libft && $(MAKE) clean
	
fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all libft ft_printf clean fclean re
