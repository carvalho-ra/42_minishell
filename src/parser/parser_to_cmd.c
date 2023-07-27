/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:29:17 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/27 01:53:53 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// funçao para pegar o número de argumentos de um comando, builtin ou não
// recebe o token de um comando e retorna o array de strings já mallocado;
// TODO

char    **ft_count_args(t_token *token)
{
    int i;
    t_token *aux;

    i = 0;
    aux = token;
    //se não for um pipe, redirecionamento ou erro?
    while (aux && (aux->type >= 0 && aux->type <= EXPAND))
    {
        i++;
        aux = aux->next;
    }
    printf("cmd / args = %i\n", i);
    if (!(aux->cmd = (char**)malloc(sizeof(char*) * (i + 1))))
        return (0);
    return (aux->cmd);
}




// ft_parse_full_cmds recebe a lista de tokens e separa em arrays de strings

void ft_parse_full_cmds(t_token *list) //fazer como int pra retornar erro;

{
    t_token *current; //vai apontar para a lista final (2a lista impressa)
    t_token *aux;
    int     i; //iterador para o array de strings

    current = list; //aponta pro primeiro nó da lista para percorrê-la sem perder a lista
    while (current) //enquanto houver nodo, aqui vou dando dup nas str dos tokens e colocando no array
    {
        if (current && (current->type == 0 && current->type <= EXPAND))
        {
            i = 0;
            current->cmd = ft_count_args(current); //retorna o array de strings já mallocado
            aux = current;//manter o ponteiro enquanto anda na lista
            while(current && (current->type >= 0 && current->type <= EXPAND)) //percorre com o auxiliar pra andar na lista
            {
                aux->cmd[i++] = ft_strdup(current->str); //copia da str para o array na posição i
                current = current->next;
            }
            current->cmd[i] = NULL;//fecha este array com a ultima string NULL
            current = current->next;//anda na lista
            if (!current)// se não houver mais nodos
                return ;//retorna
            else
                continue ;//se houver retorna pro while
        }
        else if (current && (current->type >= PIPE && current->type <= ERR))
        {
            current = current->next;
            if (!current)
                return ;
            else 
                continue ;
        }
        current = current->next;
    }
    printf("fim da lista\n");
    ft_print_cmds(list);
    return ;
}

// ft_print_cmds usada para verificar se os arrays estavam completos

void ft_print_cmds(t_token *list)
{
    write (2, "na funcao ft_print_cmds\n", 25);
    t_token *aux;
    int i;

    aux = NULL;
    aux = list;
    if (!aux)
        return ;
    while (aux)
    {
        if (aux->cmd[i])
        {
            printf("token %i mallocado\n", aux->index);
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

//ft_print_check usada para verificar se os tokens estavam sendo marcados direito
//TODO
// verificar se o token de builtin está sendo marcado corretamente (IMPORTANTE!!!)
// verificar se o token de erro está sendo marcado corretamente - FIXED in parser_utils_redirs.c
// verificar se o token de argumento está sendo marcado corretamente - nao esta sendo marcado
/*
aqui acho que é preciso uma função com a lógica do bash
- se for builtin, verifica qual é e marca (chamar a função ft_is_bultin aqui???)
tô achando que vamos acabar trabalhando com a lista, modificando ela até o final.


TODO
- depois de pipe vem um argumento, é um comando?
ou pode ser um redirecionamento? ou um pipe? ou uma builtin?

AQUI preciso de ajuda pra entender a lógica do bash e ir codando comigo algumas funções
- depois de uma builtin é um argumento? nem sempre, né? e se for um pipe? ou um redirecionamento?
quais funcionam e não funcionam? 

até então só estão excluídos os casos:
// inicia com pipe;
// termina com pipe vazio;
// termina com pipe depois de um redirecionamento - checar essa lógica
// termina com redirecionamento depois de um pipe - checar essa lógica
// pipe depois de pipe, redirecionamento depois de redirecionamento (e variações)
será que peguei todas?

- depois de um redirecionamento é um argumento?
tem que abrir arquivo? tem que armazenar o fd do arquivo? fazer fd_in e fd_out no token?
- depois de um pipe, se não for builtin, é um comando?
verificar se pode ter outras possibilidades


- redirecionamento depois de pipe? Existe? Funciona? Quais? Como? 

- pipe depois de redirecionamento? Existe? Funciona? Quais? Como?

- redirecionamento depois de builtin? Existe? Funciona? Quais? Como?

- builtin depois de redirecionamento? Existe? Funciona? Quais? Como?

- builtin depois de pipe? Existe? Funciona? Quais? Como?

- pipe depois de builtin? Existe? Funciona? Quais? Como?

- builtin depois de builtin;

*/
   
// verificar se o token de expand está sendo marcado corretamente - strings expandidas já são devolvidas nos tokens token->str;
// verificar se o token de pipe está sendo marcado corretamente - OK - eu acho
// verificar se o token de heredoc está sendo marcado corretamente - OK
// verificar se o token de redirecionamento está sendo marcado corretamente - OK
// verificar se o token de comando está sendo marcado corretamente - marcado agora, na função ft_parse_cmds



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