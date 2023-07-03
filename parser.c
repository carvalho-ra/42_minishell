#include "minishell.h"

//here we classify tokens and treat errors
int count_pipes(t_token **list)
{
    t_token *aux;
    int     i;

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

// não pode iniciar com pipe e está iniciando
// como resolver? alterar a lista para duplamente encadeada? 
// para isso precisa alterar como criar os tokens
// 

int confirm_pipe(t_token **list)
{
    t_token *aux;
    int i;

    aux = *list;
    i = 0;
    while (aux)
    {
        //pipes
        if (aux->data[0] == '|')
        {
            if (aux->next)
            {
                if (aux->next->data[0] == '|')
                {
                    aux->error = 1;
                    printf("minishell: syntax error near unexpected token `|'\n");
                    break ;
                }
            }
        }
        if (aux->data[0] == '|')
        {
            if (aux->next)
            {
                if (aux->next->data[0] != '|')
                {
                    i++;
                    aux->error = 0;
                    aux->index = 1;
                }
            }
            else
            {
                aux->error = 1;
                printf("minishell: syntax error near unexpected token `|'\n");
                break ;
            }
        }
        aux = aux->next;
    }
    return (i);
}

/*
t_token *bultins(t_token **list)
{
    t_token *aux;

    aux = *list;
    while (aux->next)
    {
        //echo
        if (ft_strcmp(aux->data, "echo") == 0)
        //cd
        if (ft_strcmp(aux->data, "cd") == 0)
        //pwd
        if (ft_strcmp(aux->data, "pwd") == 0)
        //export
        if (ft_strcmp(aux->data, "export") == 0)
        //unset
        if (ft_strcmp(aux->data, "unset") == 0)
        //env
        if (ft_strcmp(aux->data, "env") == 0)
        //exit
        if (ft_strcmp(aux->data, "exit") == 0)
    }
    return (0);
}
*/