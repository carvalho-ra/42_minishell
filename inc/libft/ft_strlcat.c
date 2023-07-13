/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:44:31 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:49:25 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	count;
	size_t	ret;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (dstsize > lendst)
		ret = lensrc + lendst;
	else
		ret = dstsize + lensrc;
	count = 0;
	while (src[count] != '\0' && lendst + 1 < dstsize)
	{
		dst[lendst++] = src[count++];
	}
	if (lendst < dstsize)
		dst[lendst] = '\0';
	return (ret);
}
