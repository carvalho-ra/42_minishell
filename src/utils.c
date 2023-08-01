/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:57 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/01 08:08:22 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// Retrieves only the key of the environment variable, up to the equal sign.
char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

// Retrieves only the value of the environment variable, after the equal sign.
char	*ft_get_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (value);
}
