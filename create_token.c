#include "minishell.h"

t_token *create_token(char *data)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->data = data;
    token->next = NULL;
    return (token);
}

