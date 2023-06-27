/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:19:07 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:52:51 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;
	size_t	counter2;

	counter = 0;
	counter2 = 0;
	if (n == 0)
		return (0);
	while (s1[counter] != '\0' && counter < n)
	{
		if (s1[counter] != s2[counter])
		{
			return (*(unsigned char *)(s1 + counter) -
					*(unsigned char *)(s2 + counter));
		}
		counter++;
	}
	while (s2[counter2] != '\0' && counter2 < n)
		counter2++;
	if (counter > counter2)
		return (1);
	if (counter < counter2)
		return (-1);
	return (0);
}
