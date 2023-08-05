/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:18:39 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/05 04:54:21 by rcarvalh         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

// To install readline:
// sudo apt-get install libreadline8; sudo apt-get install libreadline-dev

# define TRUE 1
# define FALSE 0
# define CHILD 0

typedef struct s_token
{
	int				index;
	int				type;
	int				error_code;
	char			*str;
	char			**cmd;
	struct s_shell	*shell;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char			*line;
	struct s_token	*list;
	char			**env_strs;
	struct s_env	*env;
}	t_shell;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

enum	e_token_class
{
	EXPAND = 1,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	ERR,
	CMD,
	ARG,
};

//prototypes builtins

//prototypes cd.c
int		ft_builtin_cd(t_token *current);

//prototypes cd_utils.c
int		ft_substitute_oldpwd(t_shell *shell, char *current_pwd);
int		ft_change_oldpwd(t_shell *shell, char *current_pwd);
int		ft_goto_home(t_token *current, char *current_pwd);
int		ft_goto_prev_pwd(t_token *current, char *current_pwd);
int		ft_goto_above(t_token *current, char *current_pwd);

//prototyoes echo.c
int		ft_builtin_echo(t_token *current);
char	*quotes_treatment(char *string);

//prototyoes env.c
int		ft_builtin_env(t_shell *shell);

//prototyoes exit.c
int		ft_builtin_exit(t_shell *shell);

//prototyoes export.c
int		ft_builtin_export(t_shell *shell);
int		ft_is_valid_key(char *name);
int		ft_is_key_duplicate(t_env *env, char *key, int origin);
int		ft_add_to_env_list(t_env *env_list, char *new_env, int origin);
int		ft_replace_env(t_env *env, int index, char *new_value);

//prototyoes pwd.c
int		ft_builtin_pwd(void);

//prototyoes unset.c
int		ft_builtin_unset(t_token *current);
int		ft_delete_env(t_env *env, int index);
void	ft_free_env_node(t_env *env);

//prototypes exec

//prototypes execution.c
int		ft_which_builtin(t_shell *shell, t_token *current);
int		ft_execution(t_shell *shell);

//prototypes executor.c
int		ft_env_to_str(t_shell *shell);
char	**ft_get_all_paths(t_token *current);
char	**ft_add_cmd(t_token *current, char **paths);
char	*ft_search_cmd(char **paths);
int		ft_execve(t_token *current);

//prototypes expand

//prototypes expand_utils_env.c
int		ft_copy_env(t_shell *shell, char **envp);
t_env	*ft_create_env_node(char *str);
void	ft_add_env(t_shell *shell, char *str);
char	*ft_search_env(char *str, t_shell *shell);

//prototypes expand_utils_pid.c
int		ft_aux_exp_pid_flag(char *str, int i);
char	*ft_aux_exp_pid(char *str, char *final, int i);

//prototypes expand_utils_var.c
int		ft_aux_exp_var_flag(char *str, int i);
char	*ft_aux_exp_var(char *str, char *final, int i, t_shell *shell);

//prototypes expand_utils_word.c
int		ft_aux_exp_word_flag(char *str, int i);
char	*ft_norm_aux_exp_var(char *tmp, char *final, int start, int i);
char	*ft_aux_exp_word(char *str, char *final, int i);

//prototypes expand.c
int		ft_confirm_expand(t_shell *shell);
void	ft_expand_args(t_shell *shell);
char	*ft_expand_core(char *str, t_shell *shell);
char	*ft_prep_expand(char *data);
void	ft_free_ptrs(char *str, char *str2);
void	ft_remove_quotes(t_shell *shell);

//prototypes lexer

//prototypes lexer_utils_list.c
t_token	*ft_create_node(char *str, int index, t_shell *shell);
void	ft_add_token(t_shell *shell, char *str, int index);
void	ft_print_list(t_shell *shell);

//prototypes lexer_utils_quotes.c
int		ft_single_quote(char *str, int i);
int		ft_double_quote(char *str, int i);

//prototypes lexer_utils.c
int		ft_is_blank(char c);
int		ft_is_pipe_redir(char c);
int		ft_is_pipe(char c);
int		ft_is_redir_more(char c);
int		ft_is_redir_less(char c);

//prototypes lexer.c
int		ft_aux_lexer(char *str, int i);
t_token	*ft_lexer(t_shell *shell);

//prototypes parser

//prototypes parser_join_cmds.c
char	**ft_count_args(t_token *token);
t_token	*ft_fill_array(t_token *token);
void	ft_parse_full_cmds(t_token *list);
void	ft_print_cmds(t_token *list);
void	ft_print_check(t_shell *shell);

//prototypes parser_utils_err.c
int		ft_err_pipe(t_shell *shell);
int		ft_err_redir_in(t_shell *shell);
int		ft_err_redir_out(t_shell *shell);

//prototypes parser_utils_expand.c
int		ft_confirm_expand(t_shell *shell);

//prototypes parser_utils_redirs.c
int		ft_confirm_append(t_shell *shell);
int		ft_confirm_heredoc(t_shell *shell);
int		ft_confirm_redir_out(t_shell *shell);
int		ft_confirm_redir_in(t_shell *shell);

//prototypes parser_utils.c
int		ft_count_pipes(t_shell *shell);
int		ft_count_redirs(t_shell *shell);

//prototypes parser.c
int		ft_confirm_pipe(t_shell *shell);

//prototypes main.c

//prototypes prompt
void	ft_is_history(char *str);

//prototypes signal.c
void	ft_handler(int signal);

//prototypes utils_memory.c
void	ft_free_token_list(t_shell *shell);
void	ft_free_arr_strs(char **str);
void	ft_free_env_list(t_shell *shell);
void	ft_free_env_strs(t_shell *shell);
void	ft_free_shell(t_shell *shell);

//prototypes utils.c
int		ft_strcmp(char *s1, char *s2);

#endif
