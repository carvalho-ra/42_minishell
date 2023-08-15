/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:28:38 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/15 12:10:14 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! No código implementado pelo Rodrigo, verifica-se se o token é redirecionador
//! Se for, verifica se o próximo também é. {
//!		Se for, o token atual vira erro, o próximo é o redirecionador correto.
//!		Se não for, o token atual é o redirecionador correto.

//! O que eu estou fazendo, ao identificar um token de input ou heredoc,
//! verifica se o arquivo vinculado existe e é legível. Se não for, retorna erro
//! Se for token de output ou append, verifica se o arquivo vinculado existe,
//! se não existir, cria. Se existir, verifica se é "escrevível". Senão, erro.

#include "../../inc/minishell.h"

/*void	manage_pipes(t_shell *shell)
{
	t_token	*aux;

	if (aux->output->name)
}*/

// Checks every token that has a file descriptor, and loads the input file
// to check if they're valid and readable. If not, it returns an error.
//! Se for input ou heredoc, verifica se arquivo existe e se é legível.
//! Se não for, retorna o erro correspondente.
//! Se for, abre o arquivo no modo leitura.
//TODO Possível/melhor fazer isso com matriz?
//? Reference jongoad-io.c
int	ft_load_input(struct s_token *token)
{
	t_token	*reference;

	reference = token;
	while (token)
	{
		if (token->type == REDIRECT_IN)
		{
			printf("\t\tEntrou no REDIRECT_IN\n");
			token->backup[0] = dup(STDIN_FILENO); //Salva a entrada padrão
			//token = reference;
			while (reference) //Percorre a lista até achar o "comando"
			{
				if (reference->type == FILE_NAME)
					break ;
				reference = reference->next;
			}
			token->error_code = access(reference->str, F_OK);
			if (!token->error_code) //Se arquivo existe, checa se é legível.
			{
				printf("\t\tConseguiu acessar o arquivo.\n");
				token->error_code = access(reference->str, R_OK);
			}
			printf("\t\ttoken error_code = %i\n", token->error_code);
			if (token->error_code)//Em caso de erro
			{
				if (token->error_code == 2)
					printf("minishell: %s com erro: \
							arquivo inexistente\n", reference->str);
				else
					printf("minishell: %s com erro: %s\n", \
						reference->str, strerror(token->error_code));
				return (-1);
			}
			//Se não tiver erro, abre o arquivo no modo leitura
			token->pipe[0] = open(reference->str, O_RDONLY);
			printf("\t\ttoken pipe[0] = %i\n", token->pipe[0]);
			dup2(token->pipe[0], STDIN_FILENO);
			token = reference;
		}
		token = token->next;
	}
	//close(token->pipe[0]);
	return (0);
}
//? 0644 is the permission for the file to be created (rw-r--r--)

// Checks tokens that has an output file descriptor, and loads the output file,
// that is, checks if they exists. If not, creates the file.
int	ft_load_output(struct s_token *token)
{
	t_token	*reference;

	reference = token;
	while (token)
	{
		if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			// Save the standard output to restore it later:
			token->backup[1] = dup(STDOUT_FILENO);
			//token = reference;
			while (reference)
			{
				if (reference->type == FILE_NAME)
					break ;
				reference = reference->next;
			}
			if (token->type == REDIRECT_OUT)
				token->pipe[1] = open(reference->str, \
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (token->type == APPEND)
				token->pipe[1] = open(reference->str, \
										O_WRONLY | O_CREAT | O_APPEND, 0644);
			printf("\t\tnome do arquivo: %s, fd_out: %i\n", reference->str, token->pipe[1]);
			if (token->pipe[1] < 0)
			{
				//token->error_code = errno;
				//printf("minishell: %s com erro: %s\n",
						//token->output->name, strerror(2));
				return (0);
			}
			dup2(token->pipe[1], STDOUT_FILENO);
			token = reference;
		}
		//close(token->pipe[1]);
		token = token->next;
	}
	//close(token->pipe[1]);
	return (0);
}
//? 0644 is the permission for the file to be created (rw-r--r--)

// Restores the fds to the default values (0, 1, 2)
void	ft_reset_fds(struct s_token *token)
{
	if (token->pipe[0] > 2)
	{
		close(token->pipe[0]);
		token->pipe[0] = token->backup[0];
		dup2(token->backup[0], STDIN_FILENO);
		close(token->backup[0]);
	}
	if (token->pipe[1] > 2)
	{
		close(token->pipe[1]);
		token->pipe[1] = token->backup[1];
		dup2(token->backup[1], STDOUT_FILENO);
		close(token->backup[1]);
	}
}
