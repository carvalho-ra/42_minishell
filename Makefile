NAME = minishell

SRCS = ./src/main.c \
		./src/builtins/cd_utils.c \
		./src/builtins/cd.c \
		./src/builtins/echo.c \
		./src/builtins/env.c \
		./src/builtins/exit.c \
		./src/builtins/export.c \
		./src/builtins/pwd.c \
		./src/builtins/unset.c \
		./src/expand/expand_utils_env.c \
		./src/expand/expand_utils_pid.c \
		./src/expand/expand_utils_var.c \
		./src/expand/expand_utils_word.c \
		./src/expand/expand.c \
		./src/exec/exec_utils.c \
		./src/exec/executor.c \
		./src/exec/execution.c \
		./src/lexer/lexer_utils_list.c \
		./src/lexer/lexer_utils_memory.c \
		./src/lexer/lexer_utils_quotes.c \
		./src/lexer/lexer_utils.c \
		./src/lexer/lexer.c \
		./src/parser/parser_join_cmds.c \
		./src/parser/parser_utils_err.c \
		./src/parser/parser_utils_expand.c \
		./src/parser/parser_utils_redirs.c \
		./src/parser/parser_utils.c \
		./src/parser/parser.c \
		./src/prompt.c \
		./src/signal.c \
		./src/utils_memory.c \
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

.PHONY: all clean fclean re
