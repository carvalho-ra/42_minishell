/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:35:35 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/09 01:24:48 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that checks if the first character of the key is a digit
//or an equal sign
int	ft_aux_digit(char *key)
{
	if (ft_isdigit(key[0]) || key[0] == '=')
	{
		printf("minishell: export: `%s':", key);
		printf(" não é um identificador válido\n");
		g_error_code = 1;
		return (1);
	}
	return (0);
}

// Checks if the key is valid. A key is valid if it starts with a letter or an
// underscore, and contains only alphanumeric characters or underscores.
// If the key is not valid, prints a message and returns FALSE.
// If it is valid, but doesn't have an equal sign, returns FALSE, but doesn't
// print any error message. This way it is not added to the environment list.
// If it has an equal sign, even with nothing after it, returns TRUE.
int	ft_is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_aux_digit(key) == 1)
		return (FALSE);
	while (key[i] != '=' && (ft_isalnum(key[i])
			|| key[i] == '_') && key[i] != '\0')
		i++;
	if (key[i] == '\0')
		return (FALSE);
	if (key[i] == '=' || key[i] == '\0')
	{
		g_error_code = 0;
		return (TRUE);
	}
	else
	{
		printf("minishell: export: `%s':", key);
		printf(" não é um identificador válido\n");
		g_error_code = 1;
		return (FALSE);
	}
}

// Goes through the entire list of environment variables, comparing the name of
// each node with the name passed as argument (both up to the equal sign).
//*Returns the index of the node if it finds a match, or -1 if it's unique.
//*If the origin is export (6), it compares only the keys.
int	ft_is_key_duplicate(t_env *env, char *key, int origin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env)
	{
		while (env->str[i] == key[i] && env->str[i] != '=' && key[i] != '=')
			i++;
		if ((origin == 6 && env->str[i] == '=' && key[i] == '=')
			|| (origin != 6 && env->str[i] == '='
				&& (key[i] == '\0' || key[i] == '=')))
			return (j);
		i = 0;
		j++;
		env = env->next;
	}
	return (-1);
}
