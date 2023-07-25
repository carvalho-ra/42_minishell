
#include "../../inc/minishell.h"

int ft_count_pipes(t_shell *shell)
{
    t_token *aux;

    aux = shell->list;
    while (aux)
    {
        if (aux->type == PIPE)
            i++;
        aux = aux->next;
    }
    return (i);
}

int ft_count_cmds(t_shell *shell)
{

}

int ft_count_redirs(t_shell *shell)
{
    t_token *aux;

    aux = shell->list;
    while (aux)
    {
        if (aux->type == REDIRECT_IN || aux->type == REDIRECT_OUT || aux->type == APPEND || aux->type == HEREDOC)
            i++;
        aux = aux->next;
    }
    return (i);
}

t_token **ft_full_cmd_builtin(t_token **list)
{
    t_token *aux;

    aux = &list;
    if (aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT) // se for uma BUILTIN (MUDAR no .h ?)
    {
        count = aux;
        i = 0;
        cmd_size = 0;
        while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
                && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //enquanto houver nodo
        {
            cmd_size++; //pode ser preciso inverer a linha debaixo
            count = count->next; //aponta para o próximo nó
        }
        //ainda dentro do nodo marcado com type BULITIN
        if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
            return (NULL);
        while(aux && aux->type != PIPE && aux->type != ERR
                && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
        {
            aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
            i++;
            aux = aux->next;
        }
        cmd[i] = NULL;//fecha este array com a ultima string NULL
    }
    return (&aux);
}

t_token **ft_full_cmd_no_type(t_token **list)
{
    if (aux->type == 0)
    {
        count = aux;
        i = 0;
        cmd_size = 0;
        while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
                && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //enquanto houver nodo
        {
            cmd_size++; //pode ser preciso inverer a linha debaixo
            count = count->next; //aponta para o próximo nó
        }
        //ainda dentro do nodo marcado com type 0
        if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
            return (NULL);
        while(aux && !(count->type >= PIPE &&count->type <= HEREDOC) && aux->type != ERR
                && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
        {
            aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
            i++;
            aux = aux->next;
        }
        cmd[i] = NULL;//fecha este array com a ultima string NULL
    }
    return (&aux);
}

int ft_parse_to_cmd(t_shell *shell)
{
    t_token *aux; //vai apontar para a lista final (2a lista impressa)
    t_token *count;
    int     cmd_size; //iterador para saber o tamanho da lista (número de strs) !!!precisa terminar com NULL!!!
    int     i; //iterador pra copiar a lista pro array lá no final;
    int     err_code;

    aux = shell->list; //aponta pro primeiro nó da lista para percorrê-la sem perder a lista
    //aqui vou dando dup nas str dos tokens e colocando no array
    aux = shell->list; //reaproveita o aux e aponta pro primeiro nó da lista para percorrê-la sem perder a lista
    while (aux) //enquanto houver nodo
    {
        //recebe ponteiro de ponteiro - int pra retornar erro;
        if (aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT) // se for uma BUILTIN (MUDAR no .h ?)
        {
            count = aux;
            i = 0;
            cmd_size = 0;
            while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
                    && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //enquanto houver nodo
            {
                cmd_size++; //pode ser preciso inverer a linha debaixo
                count = count->next; //aponta para o próximo nó
            }
            //ainda dentro do nodo marcado com type BULITIN
            if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
                return (NULL);
            while(aux && !(count->type >= PIPE &&count->type <= HEREDOC) && aux->type != ERR
                    && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
            {
                aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
                i++;
                aux = aux->next;
            }
            cmd[i] = NULL;//fecha este array com a ultima string NULL
        }
        if ((aux->type >= PIPE && aux->type <= HEREDOC) || aux->type == ERR)
        {
            while (aux && ((aux->type >= PIPE && aux->type <= HEREDOC) || aux-> == ERR))
                aux = aux->next;
        }
        if (aux->type == 0)
        {
            count = aux;
            i = 0;
            cmd_size = 0;
            while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
                    && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //enquanto houver nodo
            {
                cmd_size++; //pode ser preciso inverer a linha debaixo
                count = count->next; //aponta para o próximo nó
            }
            //ainda dentro do nodo marcado com type 0
            if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
                return (NULL);
            while(aux && !(count->type >= PIPE &&count->type <= HEREDOC) && aux->type != ERR
                    && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
            {
                aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
                i++;
                aux = aux->next;
            }
            cmd[i] = NULL;//fecha este array com a ultima string NULL
        }
        aux = aux->next;
    }
}

void ft_print_cmds(t_shell *shell)
{
    t_token *aux;

    aux = shell->list;
    while (aux)
    {
        i = 0;
        if (aux->cmd != NULL)
        {
            while (aux->cmd[i])
                printf (%s, aux->cmd);
        }
        aux = aux->next;
    }
}