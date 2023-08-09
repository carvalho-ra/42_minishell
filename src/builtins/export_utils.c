/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:35:35 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 21:42:16 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_aux_digit(char *name)
{
	if (ft_isdigit(name[0]))
	{
		printf("minishell: export: `%s' nome inválido\n", name);
		g_error_code = 1;
		return (1);
	}
	return (0);
}

int	ft_aux_equal(char *name, t_token *current)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (name[i] != '=' && name[i] != '\0')
		i++;
	if (name[ft_strlen(name) - 1] == '=' && !name[i + 1] && !current->cmd[2])
	{
		g_error_code = 0;
		return (0);
	}
	if (name[i] == '=' && name[i + 1] && name [i + 1] == '=')
	{
		ret = ft_substr(name, i + 1, ft_strlen(name) - i);
		printf("minishell: export: `%s':", ret);
		printf(" não é um identificador válido\n");
		ft_free_ptrs(&ret, NULL);
		g_error_code = 1;
		return (1);
	}
	return (0);
}

int	ft_aux_blank(t_token *current)
{
	if (current->cmd[2])
	{
		printf("minishell: export: `%s':", current->cmd[2]);
		printf(" não é um identificador válido\n");
		g_error_code = 1;
		return (1);
	}
	return (0);
}

// If the key is not valid, prints a message and returns FALSE.
// If it is valid, but doesn't have an equal sign, returns FALSE, but doesn't
// print any error message. This way it is not added to the environment list.
// If it has an equal sign, even with nothing after it, returns TRUE.
int	ft_is_valid_key(char *name, t_token *current)
{
	int	i;

	i = 0;
	if (ft_aux_digit(name) == 1 || ft_aux_equal(name, current) == 1
		|| ft_aux_blank(current) == 1)
		return (FALSE);
	while (name[i] != '=' && name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: nome inválido\n", 2);
			g_error_code = 1;
			return (FALSE);
		}
		i++;
	}
	if (name[i] == '=')
	{
		g_error_code = 0;
		return (TRUE);
	}
	g_error_code = 0;
	return (FALSE);
}
// A key is not valid if it starts with a number, or if it contains any
// character that is not alphanumeric or an underscore.

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
