#include "../../inc/minishell.h"

int	ft_marc_cmd(t_shell *shell)
{
	t_token	*aux;
	int		i;
	int		state;

	state = 0;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == PIPE)
			state = 0;
		if (aux->type >= 0 && aux->type <= EXPAND)
		{
			if (aux->str && state == 0)
			{
				aux->type = CMD;
				state = 1;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_marc_args(t_shell *shell)
{
	t_token	*aux;
	int		i;
	int		state;

	aux = shell->list;
	i = 0;
	while (aux)
	{
		
		if (aux->type == CMD)
			state = 0;
		if (!(aux->type >= PIPE && aux->type <= HEREDOC) && !(aux->type == CMD)
			&& !(aux->type == FILE_NAME) && !(aux->type == ERR) && !(state))
		{
			if (aux->str)
			{
				aux->type = ARG;
			}
		}
		aux = aux->next;
	}
	return (i);
}
