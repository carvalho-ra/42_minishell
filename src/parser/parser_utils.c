#include "../../inc/minishell.h"

int	ft_count_pipes(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '|')
			i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_count_redirs(t_shell *shell)
{
	t_token	*aux;
	int		i;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '>' || aux->data[0] == '<')
			i++;
		aux = aux->next;
	}
	return (i);
}
