NAME = minishell

SRCS = ./src/main.c \
		./src/builtins/env.c \
		./src/expand/expand_utils_env.c \
		./src/expand/expand_utils_pid.c \
		./src/expand/expand_utils_var.c \
		./src/expand/expand_utils_word.c \
		./src/expand/expand.c \
		./src/list.c \
		./src/lexer/lexer_utils_quotes.c \
		./src/lexer/lexer_utils.c \
		./src/lexer/lexer.c \
		./src/parser/parser_utils_builtin.c \
		./src/parser/parser_utils_err.c \
		./src/parser/parser_utils_expand.c \
		./src/parser/parser_utils_redirs.c \
		./src/parser/parser_utils.c \
		./src/parser/parser.c \
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
