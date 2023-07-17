#include "../../inc/minishell.h"

void	ft_builtin_env(t_token *new_env)
{
	t_token *aux;

	aux = new_env;
	while (aux)
	{
		printf("%s\n", aux->data);
		aux = aux->next;
	}
}