/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:30 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/19 21:21:31 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//when string initiates with | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

//when string ends with | (a pipe) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2

// redirect + PIPE é erro? ver com mais pessoas!!!!

int	ft_confirm_pipe(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	while (aux)
	{
		if (!ft_strcmp("|", aux->str) && aux->next 
			&& ft_strcmp("|", aux->next->str) && aux->type != ERR)
		{
			//set no error
			aux->error_code = 0;
			//set token type in it's structure
			aux->type = PIPE;
			printf("token %i is pipe\n", aux->index);
		}
		aux = aux->next;
	}
	return (0);
}




//next funtion was to long. it was substituted by others

// int	ft_confirm_redir(t_token **list)
// {
// 	t_token	*aux;
// 	//make a new list????
// 	//t_token	*new_list;
// 	int		i;

// 	aux = *list;
// 	i = 0;
// 	while (aux)
// 	{
// 		if (aux->data[0] == '>' && aux->next && aux->next->data[0] != '>')
// 		{
// 			i++;
// 			aux->error_code = 0;
// 			aux->type = REDIRECT_IN;
// 			printf("token %i is redirect input (<)\n", aux->index);
// 		}
// 		else if (aux->data[0] == '<' && aux->next && aux->next->data[0] != '<')
// 		{
// 			i++;
// 			aux->error_code = 0;
// 			aux->type = REDIRECT_OUT;
// 			printf("token %i is redirect output (>)\n", aux->index);
// 		}
// 		else if (aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
// 			aux->next->next && aux->next->next->data[0] != '<')
// 		{
// 			i++;
// 			aux->error_code = 0;
// 			aux->type = HEREDOC;
// 			aux = aux->next;
// 			printf("token %i is heredoc (<<)\n", aux->index);
// 		}
// 		else if (aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
// 			aux->next->next && aux->next->next->data[0] != '>')
// 		{
// 			i++;
// 			aux->error_code = 0;
// 			aux->type = APPEND;
// 			aux = aux->next;
// 			printf("token %i is append (>>)\n", aux->index);
// 		}
// 		else if ((aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
// 			aux->next->next && aux->next->next->data[0] == '<') ||
// 			(aux->data[0] == '<' && !aux->next))
// 		{
// 			//set error variable in token???
// 			aux->error_code = 2;
// 			//take thar error print to another place???
// 			printf("minishell: syntax error near unexpected token `<'\n");
// 			break ;
// 		}
// 		else if ((aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
// 			aux->next->next && aux->next->next->data[0] == '>') ||
// 			(aux->data[0] == '>' && !aux->next))
// 		{
// 			//set error variable in token???
// 			aux->error_code = 1;
// 			//take thar error print to another place???
// 			printf("minishell: syntax error near unexpected token `>'\n");
// 			break ;
// 		}
// 		aux = aux->next;
// 	}
// 	return (i);
// }
