/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:05:44 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:59:18 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dig(int n)
{
	int			digits;
	long int	n_tmp;

	digits = 0;
	n_tmp = n;
	if (n <= 0)
	{
		digits = 1;
		n_tmp = n_tmp * (-1);
	}
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			digits;
	long int	n_tmp;

	n_tmp = n;
	if (n < 0)
		n_tmp = n_tmp * (-1);
	digits = dig(n);
	nbr = malloc (sizeof(char) * digits + 1);
	if (!nbr)
		return (NULL);
	nbr[digits] = '\0';
	while (digits > 0)
	{
		digits--;
		nbr[digits] = (n_tmp % 10) + 48;
		n_tmp = n_tmp / 10;
	}
	if (n < 0)
		nbr[0] = '-';
	return (nbr);
}
