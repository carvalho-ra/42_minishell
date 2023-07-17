#include "../../inc/minishell.h"

int	ft_confirm_append(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
			aux->next->next && aux->next->next->data[0] != '>' 
			&& aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->next->type = APPEND;
			aux = aux->next;
			printf("token %i is append (>>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_confirm_heredoc(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
			aux->next->next && aux->next->next->data[0] != '<' 
			&& aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->next->type = HEREDOC;
			aux = aux->next;
			printf("token %i is heredoc (<<)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_confirm_redir_out(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '>' && aux->next && aux->next->data[0] != '>' 
			&& aux->type != APPEND && aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = REDIRECT_OUT;
			printf("token %i is redirect output (>)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_confirm_redir_in(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '<' && aux->next && aux->next->data[0] != '<' 
			&& aux->type != HEREDOC && aux->type != ERR)
		{
			i++;
			aux->error_code = 0;
			aux->type = REDIRECT_IN;
			printf("token %i is redirect input (<)\n", aux->index);
		}
		aux = aux->next;
	}
	return (i);
}
