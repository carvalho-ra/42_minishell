#include "../../inc/minishell.h"

int	ft_marc_redir_in_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == REDIRECT_IN)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_marc_redir_out_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == REDIRECT_OUT)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}

int	ft_marc_append_file(t_shell *shell)
{
	t_token	*aux;
	t_token	*tmp;
	int		i;

	tmp = NULL;
	aux = shell->list;
	i = 0;
	while (aux)
	{
		if (aux->type == APPEND)
		{
			tmp = aux->next;
			while (tmp)
			{
				if (tmp->str != NULL)
				{
					tmp->type = FILE_NAME;
					break ;
				}
				tmp = tmp->next;
			}
		}
		aux = aux->next;
	}
	return (i);
}
