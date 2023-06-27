/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:49:21 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:52:06 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	find;

	len = ((int) ft_strlen(s));
	find = (char) c;
	while (len >= 0)
	{
		if (s[len] == find)
		{
			return ((char *) &s[len]);
		}
		len--;
	}
	return (NULL);
}
