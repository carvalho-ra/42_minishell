/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 09:13:33 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/26 09:25:30 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parse_to_cmd(t_shell *shell)
{
    t_token *current; //vai apontar para a lista final (2a lista impressa)
    t_token *count;
    int     cmd_size; //iterador para saber o tamanho da lista (número de strs) !!!precisa terminar com NULL!!!
    int     i; //iterador pra copiar a lista pro array lá no final;

    current = shell->list; //aponta pro primeiro nó da lista para percorrê-la sem perder a lista
    //aqui vou dando dup nas str dos tokens e colocando no array
    while (current) //enquanto houver nodo
    {
        write(2, "here1\n", 6);
        //recebe ponteiro de ponteiro - int pra retornar erro;
        if (current->type >= BUILTIN_ECHO && current->type <= BUILTIN_EXIT) // se for uma BUILTIN (MUDAR no .h ?)
        {
            count = current;
            i = 0;
            cmd_size = 0;
            while (count && !(count->type >= PIPE && count->type <= HEREDOC) && count->type != ERR
                    && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //enquanto houver nodo
            {
                cmd_size++; //pode ser preciso inverer a linha debaixo
                count = count->next; //aponta para o próximo nó
            }
            //ainda dentro do nodo marcado com type BULITIN
            if (!(current->cmd = malloc(sizeof(char**) * cmd_size + 1)))//malloca o tamanho do array contando com o último NULL
                return ;
            count = current;
            while(count && !(count->type >= PIPE && count->type <= HEREDOC) && count->type != ERR
                    && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
            {
                current->cmd[i] = ft_strdup(count->str); //copia da str para o array na posição i
                i++;
                count = count->next;
            }
            current->cmd[i] = NULL;//fecha este array com a ultima string NULL
            current = count;
        }
        while (current && (current->type >= PIPE && current->type <= HEREDOC) && current->type == ERR)
        {
            current = current->next;
        }
        if (current->type == 0)
        {
            count = current;
            i = 0;
            cmd_size = 0;
            while (count && !(count->type >= PIPE && count->type <= HEREDOC) && count->type != ERR
                    && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //enquanto houver nodo
            {
                write(2, "here2\n", 6);
                cmd_size++; //pode ser preciso inverer a linha debaixo
                count = count->next; //aponta para o próximo nó
            }
            printf("%i\n", cmd_size);
            //ainda dentro do nodo marcado com type 0
            if (!(current->cmd = (char**)malloc(sizeof(char*) * cmd_size + 1)))//malloca o tamanho do array contando com o último NULL
                return ;
            count = current;
            printf ("%i\n", count->index);
            while(count && !(count->type >= PIPE && count->type <= HEREDOC) && count->type != ERR
                    && !(count->type >= BUILTIN_ECHO && count->type <= BUILTIN_EXIT)) //percorre com o auxiliar pra andar na lista
            {
                current->cmd[i] = ft_strdup(count->str); //copia da str para o array na posição i
                i++;                
                count = count->next;
            }
            printf ("%i\n", current->index);
            write(2, "here3\n", 6);
            while ((current && !(current->type >= PIPE && current->type <= HEREDOC) && current->type != ERR
                    && !(current->type >= BUILTIN_ECHO && current->type <= BUILTIN_EXIT)))
                    {
                        current = current->next;
                    }
            
        }
        write(2, "here4\n", 6);
        if (current->next)
            current = current->next;
        else 
            return ;
        write(2, "here5\n", 6);

    }
    return ;
}
