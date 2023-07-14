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

void	ft_add_node_bottom(t_token **list, char *str, int index)
{
	t_token *aux;

	if (*list == NULL)
		*list = ft_create_node(str, 1);
	else
	{
		aux = *list;
		while (aux->next != NULL)
		{
			index++;
			aux = aux->next;
		}
		aux->next = ft_create_node(str, index);
	}
}

void	ft_print_list(t_token *list)
{
	t_token *aux;

	aux = list;
	printf("\n");
	while (aux)
	{
		printf("token %i =  %s\n", aux->index, aux->data);
		aux = aux->next;
	}
	printf("\n");
}

void	ft_free_list(t_token **list)
{
	t_token *aux;
	
	while(*list)
	{
		aux = *list;
		free(aux->data);
		*list = (*list)->next;
		free(aux);
		aux = NULL;
	}
}