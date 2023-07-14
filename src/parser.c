#include "../inc/minishell.h"

//here we classify tokens and treat errors

//when string initiates with | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

//when string ends with | (a pipe) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2

// redirect + PIPE é erro? ver com mais pessoas!!!!

int	ft_confirm_pipe(t_token **list)
{
	t_token	*aux;

	aux = *list;
	while (aux)
	{
		if (!ft_strcmp("|", aux->data) && (!aux->next || aux == *list
			|| !ft_strcmp("|", aux->next->data)))
		{
			aux->error_code = 2;
			//take thar error message to another place!!!
			//flag? EXIT_ERROR?
			printf("minishell: syntax error near unexpected token `|'\n");
			break ;
		}
		if (!ft_strcmp("|", aux->data) && aux->next 
			&& ft_strcmp("|", aux->next->data))
		{
			//set no error
			aux->error_code = 0;
			//set token type in it's structure
			aux->type = PIPE;
			printf("is pipe\n");
		}
		aux = aux->next;
	}
	return (0);
}

// pseudocode

// look for expand ($)
// - function to iterate through strings
// of each node looking for $ (ISSUE! consider $$???)

int ft_confirm_expand(t_token **list)
{
	t_token *aux;
	int	i;
	int	flag;

	aux = *list;
	
	while (aux)
	{
		i = 0;
		flag = 0;
		while (aux->data[i])
		{
			//TODO
			//ISSUE!! if there's more than one expands in the word must expand
			// preciso dormir .....
			if (aux->data[i] == '$' && aux->data[i + 1])
			{
				flag = 1;
				i++;
				while (aux->data[i++] == '$')
					flag++;
				if (flag <= 2)
				{
					//set no error
					aux->error_code = 0;
					//set token type in it's structure
					aux->type = EXPAND;
					printf("is expand %i\n", flag);
				}
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}

//when string initiates with <> next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string initiates with > next word is the name of a file to open/create
//is opened (created) and restart the prompt
//exit status 0

//when string starts with >>> 
// bash: syntax error near unexpected token `>'
//exit error: 2


//when string initiates with >> (append) the file (named - next word)
//is opened (created) and restart the prompt

//when string initiates with >> (append) and the next char is | (a pipe) - ERROR
// bash: syntax error near unexpected token `|'
// error code: 2

// when string it ends with an append (>>) - ERROR
// bash: syntax error near unexpected token `newline'
// error code: 2



int	ft_confirm_redir(t_token **list)
{
	t_token	*aux;
	//make a new list????
	//t_token	*new_list;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '>' && aux->next && aux->next->data[0] != '>')
		{
			i++;
			aux->error_code = 0;
			aux->type = REDIRECT;
			printf("is redirect\n");
		}
		else if (aux->data[0] == '<' && aux->next && aux->next->data[0] != '<')
		{
			i++;
			aux->error_code = 0;
			aux->index = REDIRECT;
			printf("is redirect\n");
		}
		else if (aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
			aux->next->next && aux->next->next->data[0] != '<')
		{
			i++;
			aux->error_code = 0;
			aux->index = HEREDOC;
			aux = aux->next;
			printf("is heredoc\n");
		}
		else if (aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
			aux->next->next && aux->next->next->data[0] != '>')
		{
			i++;
			aux->error_code = 0;
			aux->index = APPEND;
			aux = aux->next;
			printf("is append\n");
		}
		else if ((aux->data[0] == '<' && aux->next && aux->next->data[0] == '<' &&
			aux->next->next && aux->next->next->data[0] == '<') ||
			(aux->data[0] == '<' && !aux->next))
		{
			//set error variable in token???
			aux->error_code = 2;
			//take thar error print to another place???
			printf("minishell: syntax error near unexpected token `<'\n");
			break ;
		}
		else if ((aux->data[0] == '>' && aux->next && aux->next->data[0] == '>' &&
			aux->next->next && aux->next->next->data[0] == '>') ||
			(aux->data[0] == '>' && !aux->next))
		{
			//set error variable in token???
			aux->error_code = 1;
			//take thar error print to another place???
			printf("minishell: syntax error near unexpected token `>'\n");
			break ;
		}
		aux = aux->next;
	}
	return (i);
}

int ft_is_builtin(t_token **list)
{
	t_token *aux;

	aux = *list;
	while (aux)
	{
		//echo
		if (ft_strcmp(aux->data, "echo") == 0)
		{
			aux->index = 2;
			printf("is builtin echo\n");
		}
		//cd
		if (ft_strcmp(aux->data, "cd") == 0)
		{
			aux->index = 3;
			printf("is builtin cd\n");
		}
		//pwd
		if (ft_strcmp(aux->data, "pwd") == 0)
		{
			aux->index = 4;
			printf("is builtin pwd\n");
		}
		//export
		if (ft_strcmp(aux->data, "export") == 0)
		{
			aux->index = 5;
			printf("is builtin export\n");
		}
		//unset
		if (ft_strcmp(aux->data, "unset") == 0)
		{
			aux->index = 6;
			printf("is builtin unset\n");
		}
		//env
		if (ft_strcmp(aux->data, "env") == 0)
		{
			aux->index = 7;
			printf("is builtin env\n");
		}
		//exit
		if (ft_strcmp(aux->data, "exit") == 0)
		{
			aux->index = 8;
			printf("is builtin exit");
		}
		aux = aux->next;
	}
	return (0);
}