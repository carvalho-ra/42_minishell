/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:27:53 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:57:11 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	count;
	size_t	count2;

	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstr == NULL)
		return (NULL);
	count = 0;
	count2 = 0;
	while (count < ft_strlen(s1))
	{
		newstr[count] = s1[count];
		count++;
	}
	while (count2 < ft_strlen(s2))
	{
		newstr[count] = s2[count2];
		count++;
		count2++;
	}
	newstr[count] = '\0';
	return (newstr);
}
