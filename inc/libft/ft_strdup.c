/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:41:24 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:55:42 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	count;

	result = malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (!result)
		return (NULL);
	count = 0;
	while (count < ft_strlen(s1))
	{
		result[count] = s1[count];
		count++;
	}
	result[count] = '\0';
	return (result);
}
