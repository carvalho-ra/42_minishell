#include "../inc/minishell.h"

t_token	*ft_create_node(char *str)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->data = str;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node_bottom(t_token **list, char *str)
{
	t_token *aux;

	if (*list == NULL)
		*list = ft_create_node(str);
	else
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = ft_create_node(str);
	}
}

void	ft_print_list(t_token *list)
{
	while (list)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
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