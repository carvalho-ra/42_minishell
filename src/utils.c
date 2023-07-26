/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:20:57 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/26 06:25:28 by cnascime         ###   ########.fr       */
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

// Checks whether the character in question is in the forbidden list.
int	ft_isforbidden(char character, char *forbidden)
{
	int	i;

	i = 0;
	while (forbidden[i] != '\0')
	{
		if (character == forbidden[i])
			return (1);
		i++;
	}
	if (character == '\0')
		return (1);
	return (0);
}
