/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:18:39 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/24 13:45:38 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//* 	  “Eeny-mini, teeny-weeny, shrivelled little short minishell.
//*		No! No! No! No! Don't want! Don't want! Don't want! Don't want!”
//																	Gillette.

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// To install readline:
// sudo apt-get install libreadline8; sudo apt-get install libreadline-dev

# define SUCCESS 1
# define FAILURE 0
# define TRUE 1
# define FALSE 0
# define CHILD 0

typedef struct s_token
{
	int				index;
	int				type;
	int				error_code;
	char			*str; // antes chamado data; os dois nomes não são claros; não tem de ser char**?
	struct s_shell	*shell;
	struct s_token	*next;
}	t_token;

//AO FAZER NOVA STRUCT PARA MINISHELL
typedef struct s_shell
{
	char			*line; //chamar direto da readline pra cá
	//char			*expanded;
	char			**envp;
	struct s_token	*list; // isso é a linha, mas separada em tokens?
	struct s_token	*new_env; // mudar esse nome
}	t_shell;

typedef struct	s_env
{
	int				index;
	char			*str;
	struct s_env	*next;
}	t_env;

//fazer função para repassar a lista (excluir nó do meio e dar free!!!)
// passar head + posição (INDEX)

enum	e_token_class
{
	PIPE = 1,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	CMD,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	WORD,
	EXPAND,
	ERR
};

//prototypes builtins
int		ft_builtin_cd(t_shell *shell);
int		ft_builtin_echo(t_shell *shell);
int		ft_builtin_env(t_shell *shell);
int		ft_builtin_export(t_shell *shell);
int		ft_builtin_pwd(void);

//builtin utils
char	*quotes_treatment(char *string);
int		ft_is_valid_env_name(char *name);

//prototypes lexer utils quotes
int		ft_single_quote(char *str, int i);
int		ft_double_quote(char *str, int i);

//prototypes lexer utils
int		ft_is_blank(char c);
int		ft_is_pipe_redir(char c);
int		ft_is_pipe(char c);
int		ft_is_redir_more(char c);
int		ft_is_redir_less(char c);

//prototypes lexer
t_token	*ft_lexer(t_shell *shell);

//prototype parser utils bultin
int		ft_is_builtin(t_shell *shell);

//prototypes parser utils err
int		ft_err_pipe(t_shell *shell);
int		ft_err_redir_in(t_shell *shell);
int		ft_err_redir_out(t_shell *shell);

//prototypes parser utils redirs
int		ft_confirm_append(t_shell *shell);
int		ft_confirm_heredoc(t_shell *shell);
int		ft_confirm_redir_out(t_shell *shell);
int		ft_confirm_redir_in(t_shell *shell);

//prototypes parser utils
int		ft_count_pipes(t_shell *shell);
int		ft_count_redirs(t_shell *shell);

//prototypes parser
int		ft_confirm_pipe(t_shell *shell);

//prototypes expand utils env
int		ft_copy_env(t_shell *shell, char **envp);
char	*ft_search_env(char *str, t_shell *shell);

//prototypes expand utils pid
int		ft_aux_exp_pid_flag(char *str, int i);
char	*ft_aux_exp_pid(char *str, char *final, int i);

//prototypes expand utils var
int		ft_aux_exp_var_flag(char *str, int i);
char	*ft_aux_exp_var(char *str, char *final, int i, t_shell *shell);

//prototypes expand utils word
int		ft_aux_exp_word_flag(char *str, int i);
char	*ft_norm_aux_exp_var(char *tmp, char *final, int start, int i);
char	*ft_aux_exp_word(char *str, char *final, int i);

//prototypes expand
int		ft_confirm_expand(t_shell *shell);
void	ft_expand_args(t_shell *shell);
char	*ft_prep_expand(char *str);
char	*ft_expand_core(char *str, t_shell *shell);
char	*ft_prep_expand(char *data);
void	ft_free_ptrs(char *str, char *str2);

//prototypes list
t_token	*ft_create_node(char *str, int index);
void	ft_add_token(t_shell *shell, char *str, int index);
void	ft_add_env(t_shell *shell, char *str, int index);
void	ft_print_list(t_shell *shell);
void	ft_free_token_list(t_shell *shell);
void	ft_free_env_list(t_shell *shell);
void	ft_free_shell(t_shell *shell);

//prototypes prompt
void	ft_is_history(char *str);

//prototypes signal
void	ft_handler(int signal);

//utils
int		ft_strcmp(char *s1, char *s2);

#endif
