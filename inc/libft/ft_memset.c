/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:21:59 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:45:57 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*tmp;

	index = 0;
	tmp = (unsigned char *) b;
	while (index < len)
	{
		tmp[index] = c;
		index++;
	}
	return (b);
}
