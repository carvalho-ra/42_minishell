#include "minishell.h"

void    print_tokens(t_token *tokens_list)
{
    t_token *aux;
    
    aux = tokens_list;
    while (aux)
    {
        printf("%s", tokens_list->data);
        aux = aux->next;
    }
}

t_token	*split(char *str)
{
	char    **tokens_arr;
    t_token *tokens_list;
    int i;

    tokens_list = malloc(sizeof(t_token*));
	if (!str)
		return (NULL);
    i = 0;
    tokens_arr = ft_split(str, ' ');
    while(tokens_arr[i])
    {
        create_node(str);
        i++;
    }
    return (tokens_list);
}
