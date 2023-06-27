/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:30:59 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/06/28 17:52:34 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	int		count;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_s = malloc (sizeof (char) * len + 1);
	if (!new_s)
		return (NULL);
	count = 0;
	while (count < len)
	{
		new_s[count] = (*f)(count, s[count]);
		count++;
	}
	new_s[count] = '\0';
	return (new_s);
}
