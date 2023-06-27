/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:09:02 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 14:17:55 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	count;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		sub = malloc (ft_strlen(s) + 1);
	else
		sub = malloc ((sizeof(char) * len) + 1);
	if (!sub)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (i >= start && count < len)
		{
			sub[count] = s[i];
			count++;
		}
		i++;
	}
	sub[count] = '\0';
	return (sub);
}
