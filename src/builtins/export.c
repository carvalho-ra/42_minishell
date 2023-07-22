/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:39:40 by cnascime          #+#    #+#             */
/*   Updated: 2023/07/22 13:09:30 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// 
int	ft_builtin_export(t_shell *shell)
{
	t_token	*aux;

	aux = shell->list;
	if (ft_is_valid_env_name(aux->data))
	{
		//TODO comparar cada item da lista de variáveis de ambiente
		//TODO se já existir, sobrescrever
		//TODO se não existir, criar
	}
	else
	{
		ft_putstr_fd("minishell: export: nome inválido\n", 2);
		return (1); // retorno em caso de erro
	}
	//return (1); //retorno original deveria ser 0, mas a função que chama
	// pergunta se é builtin, então o esperado seria TRUE.
}

int	ft_is_valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// The export builtin adds the variable name to the environment with the value
// value, if name doesn't already exist. If name does exist in the environment,
// then its value is changed to value if overwrite is nonzero; if overwrite is
// zero, then the value of name is not changed. This builtin returns true unless
// an invalid option is given or name is read-only.
//
// If the name argument contains a ‘=’, then the export builtin assigns a value
// to the environment variable name. Otherwise, the environment variable name is
// removed from the environment of the executed command.
//
// The return status is zero unless an invalid option is encountered, an attempt
// is made to define a function using ‘-f foo=bar’, an attempt is made to export
// a function using the ‘-f’ option with a name that is not a valid function
// name, an attempt is made to export an array variable using the ‘-a’ option,
// one of the names is not a valid shell variable name, an attempt is made to
// export a variable that is not an integer, etc.
//
// To mimic the export bash command, we need to check if the variable name is
// valid. A valid variable name is any string of alphanumeric characters, plus
// the underscore, not starting with a number. We also need to check if the
// variable name is already in the environment. If it is, we need to change its
// value. If it isn't, we need to add it to the environment.
//