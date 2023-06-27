/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:19:01 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:47:23 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst2;
	const char	*src2;

	if (dst == src || n == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	dst2 = (char *)dst;
	src2 = (const char *)src;
	while (n--)
	{
		dst2[n] = src2[n];
	}
	return (dst);
}
