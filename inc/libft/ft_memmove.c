/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:33:05 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:48:06 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	count;

	count = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if ((size_t)dst - (size_t)src < len)
		ft_memcpy(dst, src, len);
	else
	{	
		while (count < len)
		{
			((unsigned char *)dst)[count] = ((unsigned char *)src)[count];
			count++;
		}
	}
	return (dst);
}
