#include "../../inc/minishell.h"

void	ft_builtin_env(t_shell *shell)
{
	t_token *aux;

	aux = shell->new_env;
	while (aux)
	{
		printf("%s\n", aux->data);
		aux = aux->next;
	}
}