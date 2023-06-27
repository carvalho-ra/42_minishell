/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:39:20 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:54:20 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c1;
	size_t	c2;

	c1 = 0;
	c2 = 0;
	if (needle[0] == '\0' || needle == NULL)
		return ((char *)haystack);
	while (c1 <= len && haystack[c1] != '\0')
	{
		c2 = 0;
		while (haystack[c1 + c2] == needle[c2] && c1 + c2 < len)
		{
			if (needle[c2 + 1] == '\0')
				return ((char *)&haystack[c1]);
			c2++;
		}
		c1++;
	}
	return (NULL);
}
