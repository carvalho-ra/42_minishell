/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:53:23 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:53:18 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	counter;
	char	find;
	char	*word;

	word = (char *)s;
	find = (unsigned char) c;
	counter = 0;
	while (counter < n)
	{
		if (word[counter] == find)
		{
			return (&word[counter]);
		}
		counter++;
	}
	return (NULL);
}
