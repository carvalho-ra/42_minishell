#include "minishell.h"

t_token	*create_node(char *str)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->data = str;
	new_node->next = NULL;
	return (new_node);
}

void	add_node_bottom(t_token **list, char *str)
{
	t_token *aux;

	if (*list == NULL)
		*list = create_node(str);
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = create_node(str);
	}
}

void	print_list(t_token *list)
{
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

void	free_list(t_token **list)
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