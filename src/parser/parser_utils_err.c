#include "../../inc/minishell.h"

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

