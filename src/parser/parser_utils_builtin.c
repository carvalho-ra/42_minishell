#include "../../inc/minishell.h"

int ft_is_builtin(t_shell *shell)
{
	t_token *aux;

	aux = shell->list;
	while (aux)
	{
		//echo
		if (ft_strcmp(aux->data, "echo") == 0)
		{
			aux->type = BUILTIN_ECHO;
			printf("token %i is builtin echo\n", aux->index);
		}
		//cd
		if (ft_strcmp(aux->data, "cd") == 0)
		{
			aux->type = BUILTIN_CD;
			printf("token %i is builtin cd\n", aux->index);
		}
		//pwd
		if (ft_strcmp(aux->data, "pwd") == 0)
		{
			aux->type = BUILTIN_PWD;
			printf("token %i is builtin pwd\n", aux->index);
		}
		//export
		if (ft_strcmp(aux->data, "export") == 0)
		{
			aux->type = BUILTIN_EXPORT;
			printf("token %i is builtin export\n", aux->index);
		}
		//unset
		if (ft_strcmp(aux->data, "unset") == 0)
		{
			aux->type = BUILTIN_UNSET;
			printf("token %i is builtin unset\n", aux->index);
		}
		//env
		if (ft_strcmp(aux->data, "env") == 0)
		{
			aux->type = BUILTIN_ENV;
			printf("token %i is builtin env\n", aux->index);
		}
		//exit
		if (ft_strcmp(aux->data, "exit") == 0)
		{
			aux->type = BUILTIN_EXIT;
			printf("token %i is builtin exit\n", aux->index);
		}
		aux = aux->next;
	}
	return (0);
}