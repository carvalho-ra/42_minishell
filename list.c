#include "minishell.h"

t_token	*create_node(char *str)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->data = str;
	new_node->next = NULL;
	return (new_node);
}

void	add_node_bottom(t_token **list, char *str)
{
	if (list == NULL)
	{
		printf("here");
		*list = create_node(str);
	}
	else
	{
		while (list)
			list = &(*list)->next;
		*list = create_node(str);
	}
}
