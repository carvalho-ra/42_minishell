/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:29:17 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/26 14:23:02 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int ft_count_pipes(t_shell *shell)
// {
//     t_token *aux;

//     aux = shell->list;
//     while (aux)
//     {
//         if (aux->type == PIPE)
//             i++;
//         aux = aux->next;
//     }
//     return (i);
// }

// int ft_count_cmds(t_shell *shell)
// {

// }

// int ft_count_redirs(t_shell *shell)
// {
//     t_token *aux;

//     aux = shell->list;
//     while (aux)
//     {
//         if (aux->type == REDIRECT_IN || aux->type == REDIRECT_OUT || aux->type == APPEND || aux->type == HEREDOC)
//             i++;
//         aux = aux->next;
//     }
//     return (i);
// }

// t_token **ft_full_cmd_builtin(t_token **list)
// {
//     t_token *aux;

//     aux = &list;
//     if (aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT) // se for uma BUILTIN (MUDAR no .h ?)
//     {
//         count = aux;
//         i = 0;
//         cmd_size = 0;
//         while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
//                 && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //enquanto houver nodo
//         {
//             cmd_size++; //pode ser preciso inverer a linha debaixo
//             count = count->next; //aponta para o próximo nó
//         }
//         //ainda dentro do nodo marcado com type BULITIN
//         if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
//             return (NULL);
//         while(aux && aux->type != PIPE && aux->type != ERR
//                 && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
//         {
//             aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
//             i++;
//             aux = aux->next;
//         }
//         cmd[i] = NULL;//fecha este array com a ultima string NULL
//     }
//     return (&aux);
// }

// t_token **ft_full_cmd_no_type(t_token **list)
// {
//     if (aux->type == 0)
//     {
//         count = aux;
//         i = 0;
//         cmd_size = 0;
//         while (count && !(count->type >= PIPE &&count->type <= HEREDOC) && count->type != ERR
//                 && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //enquanto houver nodo
//         {
//             cmd_size++; //pode ser preciso inverer a linha debaixo
//             count = count->next; //aponta para o próximo nó
//         }
//         //ainda dentro do nodo marcado com type 0
//         if (!(aux->cmd = malloc(sizeoff(char**) * cmd_size + 1)));//malloca o tamanho do array contando com o último NULL
//             return (NULL);
//         while(aux && !(count->type >= PIPE &&count->type <= HEREDOC) && aux->type != ERR
//                 && !(aux->type >= BUILTIN_ECHO && aux->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
//         {
//             aux->cmd[i] = ft_strdup(aux->str); //copia da str para o array na posição i
//             i++;
//             aux = aux->next;
//         }
//         cmd[i] = NULL;//fecha este array com a ultima string NULL
//     }
//     return (&aux);
// }

void ft_parse_to_cmd(t_shell *shell)
{
    t_token *current; //vai apontar para a lista final (2a lista impressa)
    t_token *count;
    int     cmd_size; //iterador para saber o tamanho da lista (número de strs) !!!precisa terminar com NULL!!!
    int     i; //iterador pra copiar a lista pro array lá no final;

    current = shell->list; //aponta pro primeiro nó da lista para percorrê-la sem perder a lista
    //aqui vou dando dup nas str dos tokens e colocando no array
    while (current) //enquanto houver nodo
    {
        //recebe ponteiro de ponteiro - int pra retornar erro;
        if (current->type >= BUILTIN_ECHO && current->type <= BUILTIN_EXIT) // se for uma BUILTIN (MUDAR no .h ?)
        {
            count = current;
            i = 0;
            cmd_size = 0;
            while (count && (count->type == EXPAND || count->type == 0
                    || (count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT))) //enquanto houver nodo e for uma BUILTIN ou 0 ou EXPAND
            {
                cmd_size++;
                count = count->next; //aponta para o próximo nó
            }
            //ainda dentro do nodo marcado com type BUILTIN
            if (!(current->cmd = (char**)malloc(sizeof(char*) * (cmd_size + 1))))//malloca o tamanho do array contando com o último NULL
                return ;
            //current->cmd[i++] = ft_strdup(current->str);
            count = current;
            while(count && (count->type == EXPAND || count->type == 0
                    || (count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT))) // enquanto for uma BUILTIN ou 0 ou EXPAND
            {
                current->cmd[i] = ft_strdup(count->str); //copia da str para o array na posição i
                i++;
                count = count->next;
            }
            current->cmd[i] = NULL;//fecha este array com a ultima string NULL
            while (current && (current->type == EXPAND || current->type == 0
                    || (current->type >= BUILTIN_ECHO && current->type <= BUILTIN_EXIT))) // enquanto for uma BUILTIN ou 0 ou EXPAND
                current = current->next;
            if (!current)
                return ;
        }
        if (current && current->type == ERR)
        {
            current = current->next;
        }
        if (current && (current->type >= PIPE && current->type <= HEREDOC))
        {
            current = current->next;
        }
        if (current->type == EXPAND || current->type == 0)
        {
            count = current;
            i = 0;
            cmd_size = 0;
            while (count && (count->type == EXPAND || count->type == 0)) //enquanto houver nodo
            {
                cmd_size++; //pode ser preciso inverer a linha debaixo
                count = count->next; //aponta para o próximo nó
            }
            //ainda dentro do nodo marcado com type 0
            if (!(current->cmd = (char**)malloc(sizeof(char*) * (cmd_size + 1))))//malloca o tamanho do array contando com o último NULL
                return ;
            count = current;
            while(count && (count->type == EXPAND || count->type == 0)) //percorre com o auxiliar pra andar na lista
            {
                current->cmd[i] = ft_strdup(count->str); //copia da str para o array na posição i
                i++;                
                count = count->next;
            }
            current->cmd[i] = NULL;//fecha este array com a ultima string NULL
            while (current && (current->type == EXPAND || current->type == 0))
                current = current->next;
            if (!current)// se não houver mais nodos
                return ; 
        }
        current = current->next;
    }
    return ;
}

void ft_print_cmds(t_shell *shell)
{
    t_token *aux;
    int i;

    aux = NULL;
    aux = shell->list;
    if (!aux)
        return ;
    while (aux)
    {
        if (aux->cmd)
        {
            printf("token %i\n", aux->index);
            i = 0;
            while (aux->cmd[i])
            {
                printf ("%s\n", aux->cmd[i]);
                i++;
                if (aux->cmd[i] == NULL)
                    printf("NULL\n"); 
            }
        }
        aux = aux->next;
    }
}

void ft_print_check(t_shell *shell)
{
    t_token *aux;

    aux = NULL;
    aux = shell->list;
    if (!aux)
        return ;
    while (aux)
    {
        if (aux->type)
        {
            printf("token index %i\n", aux->index);
            printf("token type %i\n", aux->type);
        }
        aux = aux->next;
    }
}