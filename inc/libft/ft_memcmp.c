/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:10:20 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:53:48 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*word1;
	unsigned char	*word2;	
	size_t			counter;

	word1 = (unsigned char *)s1;
	word2 = (unsigned char *)s2;
	counter = 0;
	while (counter < n)
	{
		if (word1[counter] != word2[counter])
		{	
			return (word1[counter] - word2[counter]);
		}
		counter++;
	}
	return (0);
}
