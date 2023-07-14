NAME = minishell

SRCS = ./src/main.c \
		./src/builtins/env.c \
		./src/expand.c \
		./src/list.c \
		./src/lexer_utils.c \
		./src/lexer.c \
		./src/parser_utils.c \
		./src/parser.c \
		./src/prompt.c \
		./src/signal.c \
		./src/utils.c \

OBJS = $(SRCS:.c=.o)

INC = -Iinc/libft -Linc/libft -lft 

LIBFT = inc/libft/libft.a

CC = cc -g -Wall -Wextra -Werror

all: $(NAME)

$(LIBFT):
	cd inc/libft && $(MAKE)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)
	cd inc/libft && $(MAKE) clean
	
fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all libft ft_printf clean fclean re
