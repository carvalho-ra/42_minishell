/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:57:05 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/06/28 18:17:56 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	len;
	int	count;

	if (!s)
		return ;
	len = ft_strlen(s);
	count = 0;
	while (count < len)
	{
		f(count, &s[count]);
		count++;
	}
}
