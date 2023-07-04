#include "minishell.h"

//here we classify tokens and treat errors

int	count_pipes(t_token **list)
{
	t_token	*aux;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '|')
			i++;
		aux = aux->next;
	}
	return (i);
}

int	confirm_pipe(t_token **list)
{
	t_token	*aux;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '|' && (!aux->next || aux == *list ||
		 aux->next->data[0] == '|'))
		{
			//set error variable in token???
			aux->error = 1;
			//take thar error print to another place???
			printf("minishell: syntax error near unexpected token `|'\n");
			break ;
		}
		if (aux->data[0] == '|' && aux->next && aux->next->data[0] != '|')
		{
			i++;
			aux->error = 0;
			aux->index = 1;
		}
		aux = aux->next;
	}
	return (i);
}

int is_builtin(t_token **list)
{
	t_token *aux;

	aux = *list;
	while (aux)
	{
		//echo
		if (ft_strcmp(aux->data, "echo") == 0)
		{
			aux->index = 2;
			printf("is builtin echo\n");
		}
		//cd
		if (ft_strcmp(aux->data, "cd") == 0)
		{
			aux->index = 3;
			printf("is builtin cd\n");
		}
		//pwd
		if (ft_strcmp(aux->data, "pwd") == 0)
		{
			aux->index = 4;
			printf("is builtin pwd\n");
		}
		//export
		if (ft_strcmp(aux->data, "export") == 0)
		{
			aux->index = 5;
			printf("is builtin export\n");
		}
		//unset
		if (ft_strcmp(aux->data, "unset") == 0)
		{
			aux->index = 6;
			printf("is builtin unset\n");
		}
		//env
		if (ft_strcmp(aux->data, "env") == 0)
		{
			aux->index = 7;
			printf("is builtin env\n");
		}
		//exit
		if (ft_strcmp(aux->data, "exit") == 0)
		{
			aux->index = 8;
			printf("is builtin exit");
		}
		aux = aux->next;
	}
	return (0);
}