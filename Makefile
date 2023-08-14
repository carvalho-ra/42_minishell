MAKEFLAGS	=	--silent

NAME = minishell

SRCS = ./src/main.c \
		./src/builtins/cd_utils.c \
		./src/builtins/cd.c \
		./src/builtins/echo.c \
		./src/builtins/env.c \
		./src/expand.c \
		./src/list.c \
		./src/lexer/lexer_utils_quotes.c \
		./src/lexer/lexer_utils.c \
		./src/lexer/lexer.c \
		./src/parser/parser_join_cmds.c \
		./src/parser/parser_mark_cmds_args.c \
		./src/parser/parser_mark_files_keyword.c \
		./src/parser/parser_marks.c \
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

CC = gcc -g -Wall -Wextra -Werror

all: $(NAME)

$(LIBFT):
	cd inc/libft && $(MAKE)

%.o: %.c
#	$(CC) -c $< -o $@
	@${CC} -c $< -o ${<:.c=.o}
	@printf "\033[0;32m#\e[m"

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME) -lreadline
	@printf "\033[0;33m miniSHELL compilation OK\e[m\n"

clean:
	rm -f $(OBJS)
	cd inc/libft && $(MAKE) clean
	@printf "\033[0;33m miniSHELL cleaned\e[m\n"

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

val: re
	rm -f $(OBJS)
	cd inc/libft && $(MAKE) clean
	@printf "\033[0;33m miniSHELL cleaned\e[m\n"
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
