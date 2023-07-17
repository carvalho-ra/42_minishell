#include "../inc/minishell.h"

t_token	*ft_create_node(char *str, int index)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->index = index;
	new_node->data = str;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_token(t_shell *shell, char *str, int index)
{
	t_token *aux;

	aux = NULL;
	aux = shell->list;
	if (aux == NULL)
		shell->list = ft_create_node(str, 1);
	else
	{
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index);
	}
}

void	ft_add_env(t_shell *shell, char *str, int index)
{
	t_token *aux;

	aux = shell->new_env;
	if (aux == NULL)
		shell->new_env = ft_create_node(str, 0);
	else
	{
		aux = shell->new_env;
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index);
	}
}

void	ft_print_list(t_shell *shell)
{
	t_token *aux;

	aux = shell->list;
	while (aux)
	{
		printf("token %i =  %s\n", aux->index, aux->data);
		aux = aux->next;
	}
}

void	ft_free_token_list(t_shell *shell)
{
	t_token *aux;
	
	aux = shell->list;
	while(aux)
	{
		free(aux->data);
		aux = aux->next;
		free(shell->list);
		shell->list = aux;
	}
}

void	ft_free_env_list(t_shell *shell)
{
	t_token *aux;
	
	aux = shell->new_env;
	while(aux)
	{
		free(aux->data);
		aux = aux->next;
		free(shell->new_env);
		shell->new_env = aux;
	}
}

//AO FAZER NOVA STRUCT PARA MINISHELL

void	ft_free_shell(t_shell *shell)
{
	t_shell *aux;
	
	aux = shell;
	free(aux->new_env);
	free(aux->list);
	free(shell);
}