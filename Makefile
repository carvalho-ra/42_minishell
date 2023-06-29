NAME = minishell

SRCS = main.c \
		history.c \
		list.c \
		prompt.c \
		signal.c \
		tokenization.c \
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
