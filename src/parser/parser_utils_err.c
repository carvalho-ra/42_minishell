#include "../../inc/minishell.h"

//when string initiates with <> next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string initiates with > next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string starts with >>> 
// bash: syntax error near unexpected token `>'
//exit error: 2

//when string initiates with >> (append) the file (named - next word)
//is opened (created) and restart the prompt

//when string initiates with >> (append) and the next char is | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

// when string it ends with an append (>>) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2

int	ft_err_pipe(t_token **list)
{
	t_token	*aux;

	aux = *list;
	while (aux)
	{
		if (!ft_strcmp("|", aux->data) && (!aux->next || aux == *list
			|| !ft_strcmp("|", aux->next->data)))
		{
			aux->error_code = 2;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->data[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("token %i, minishell: syntax error near unexpected token `|'\n", aux->index);
			break ;
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_err_redir_in(t_token **list)
{
	t_token	*aux;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if ((aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
			aux->next->next && ft_is_pipe_redir(aux->next->next->data[0])) ||
			(aux->data[0] == '<' && !aux->next))
		{
			aux->error_code = 1;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->data[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("token %i, minishell: syntax error near unexpected token `<'\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_err_redir_out(t_token **list)
{
	t_token	*aux;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if ((aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
			aux->next->next && ft_is_pipe_redir(aux->next->next->data[0]))
			|| (aux->data[0] == '>' && !aux->next))
		{
			aux->error_code = 1;
			aux->type = ERR;
			while (aux->next && ft_is_pipe_redir(aux->next->data[0]))
			{
				aux->next->type = ERR;
				aux = aux->next;
			}
			printf("token %i, minishell: syntax error near unexpected token `>'\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}
