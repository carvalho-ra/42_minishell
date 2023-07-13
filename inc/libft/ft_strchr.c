/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:07:06 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:51:10 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		counter;
	int		len;
	char	find;

	len = ((int) ft_strlen(s));
	find = (char) c;
	counter = 0;
	while (counter <= len)
	{
		if (s[counter] == find)
		{
			return ((char *) &s[counter]);
		}
		counter++;
	}
	return (NULL);
}
