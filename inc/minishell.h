/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:18:39 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/21 21:36:11 by rcarvalh         ###   ########.fr       */
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
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

// To install readline:
// sudo apt-get install libreadline8; sudo apt-get install libreadline-dev

# define TRUE 1
# define FALSE 0
# define CHILD 0

extern int	g_error_code;

typedef struct s_token
{
	int				index;
	int				type;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	int				backup[2];
	int				error_code;
	char			*str;
	char			**cmd;
	int				join;
	struct s_shell	*shell;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char			*line;
	struct s_token	*list;
	char			**env_strs;
	struct s_env	*env;
	int				pipe[2];
	int				backup[2];
	int				aux_lexer;
	char			*temp_str;
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
	FILE_NAME,
	KEYWORD,
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

//prototypes echo.c
int		ft_builtin_echo(t_token *current);
char	*quotes_treatment(char *string);

//prototypes env.c
int		ft_builtin_env(t_token *current);

//prototypes exit.c
int		ft_free_exit(t_shell *shell);
int		ft_free_no_exit(t_shell *shell);
int		ft_builtin_exit(t_token *current);

//prototypes export_env_utils.c
int		ft_add_to_env_list(t_env *env_list, char *new_env, int origin);
int		ft_replace_env(t_env *env, int index, char *new_value);

//prototypes export_utils.c
int		ft_aux_digit(char *key);
int		ft_is_valid_key(char *key);
int		ft_is_key_duplicate(t_env *env, char *key, int origin);

//prototypes export.c
int		ft_builtin_export(t_token *current);

//prototypes pwd.c
int		ft_builtin_pwd(void);

//prototypes unset.c
int		ft_builtin_unset(t_token *current);
int		ft_delete_env(t_env *env, int index);
void	ft_free_env_node(t_env *env);

//prototypes exec

//prototypes exec_utils.c
int		ft_env_to_str(t_shell *shell);
void	ft_print_error_msg(char *str, char *msg, int error_code);
void	ft_signal_reset(void);
int		ft_is_dir(char *path);
int		ft_is_executable(char *str);

//prototypes execution.c
int		ft_which_builtin(t_token *current);
int		ft_master_exec(t_shell *shell);
t_token	*ft_execution(t_token *current);

//prototypes executor.c
int		ft_check_cmd(t_token *current);
int		ft_execve(t_token *current, char *cmd);
int		ft_execve_core(t_token *current, char *cmd);

//prototypes mount_cmd.c
char	**ft_get_all_paths(t_token *current);
char	**ft_add_cmd(t_token *current, char **paths);
char	*ft_search_cmd(char **paths);

//prototypes expand

//prototypes expand_utils_env.c
int		ft_copy_env(t_shell *shell, char **envp);
t_env	*ft_create_env_node(char *str);
void	ft_add_env(t_shell *shell, char *str);
char	*ft_search_env(char *str, t_shell *shell);

//prototypes expand_utils_err.c
int		ft_aux_exp_err_flag(char *str, int i);
char	*ft_aux_exp_err(char *str, char *final, int i);

//prototypes expand_utils_pid.c
int		ft_aux_exp_pid_flag(char *str, int i);
char	*ft_aux_exp_pid(char *str, char *final, int i);

//prototypes expand_utils_var.c
int		ft_aux_exp_var_flag(char *str, int i);
char	*ft_norm_aux_exp_var(char *tmp, char *final, int start, int i);
char	*ft_aux_exp_var(char *str, char *final, int i, t_shell *shell);

//prototypes expand_utils_word.c
int		ft_aux_exp_word_flag(char *str, int i);
char	*ft_aux_exp_word(char *str, char *final, int i);

//prototypes expand.c
void	ft_expansion(t_shell *shell);
void	ft_expand_args(t_shell *shell);
char	*ft_expand_core(char *str, t_shell *shell);
void	ft_remove_quotes(t_shell *shell);
void	ft_join_from_lexer(t_shell *shell);

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

//prototypes parser_marc_cmd_args.c
int		ft_mark_cmds(t_shell *shell);
int		ft_mark_args(t_shell *shell);

//prototypes parser_marc_files.c
int		ft_mark_redir_in_file(t_shell *shell);
int		ft_mark_redir_out_file(t_shell *shell);
int		ft_mark_append_file(t_shell *shell);
int		ft_mark_heredoc_keyword(t_shell *shell);

//prototypes parser_marcs.c
int		ft_marks(t_shell *shell);

//prototypes parser_utils_err.c
int		ft_err_pipe(t_shell *shell);
int		ft_err_redir_in(t_shell *shell);
int		ft_err_redir_out(t_shell *shell);

//prototypes parser_utils_expand.c
int		ft_set_quote_state(char *str, int state, int i);
int		ft_confirm_expand(t_shell *shell);

//prototypes parser_utils_redirs.c
int		ft_confirm_pipe(t_shell *shell);
int		ft_confirm_append(t_shell *shell);
int		ft_confirm_heredoc(t_shell *shell);
int		ft_confirm_redir_out(t_shell *shell);
int		ft_confirm_redir_in(t_shell *shell);

//prototypes parser.c
int		ft_validation(t_shell *shell);
int		ft_parser(t_shell *shell);
int		ft_final_list(t_shell *shell);

//prototypes pipes

//prototypes pipes_utils.c
int		ft_count_pipes(t_shell *shell);
int		ft_count_redir_in(t_shell *shell);
int		ft_count_cmds(t_shell *shell);

//prototypes pipes.c
int		ft_load_pipes(t_token *list);
void	ft_set_pipe_fds(t_token *token_cmd, t_token *token_pipe);
void	ft_reset_pipe_fds(t_token *token_cmd);

//prototypes redirector

//prototypes handle_fds.c
void	ft_set_fds(struct s_token *token);
void	ft_reset_fds(struct s_token *token);

//prototypes redirector.c
int		ft_redirector(struct s_token *token);
char	*ft_get_name(t_token *token);
int		ft_load_input(struct s_token *token, char *filename);
int		ft_load_output(struct s_token *token, char *filename, int type);

//prototypes heredoc.c
int		ft_load_heredoc(t_token *token, char *delimiter);

//prototypes main.c
void	ft_shell(t_shell *shell);

//prototypes prompt
int		ft_is_history(char *str);

//prototypes signal.c
void	ft_handler(int signal);

//prototypes utils_memory.c
void	ft_free_token_list(t_shell *shell);
void	ft_free_arr_strs(char **str);
void	ft_free_env_list(t_shell *shell);
void	ft_free_env_strs(t_shell *shell);
void	ft_free_shell(t_shell *shell);
void	ft_free_ptrs(char **str, char **str2);

//prototypes utils.c
int		ft_strcmp(char *s1, char *s2);

#endif