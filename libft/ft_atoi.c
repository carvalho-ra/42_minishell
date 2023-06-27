/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:19:47 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:54:49 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		result;
	size_t	count;
	int		sign;

	sign = 1;
	result = 0;
	count = 0;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign *= -1;
		count++;
	}
	while (ft_isdigit(str[count]) == 1)
	{
		result = (result * 10) + (str[count] - '0');
		count++;
	}
	return (result * sign);
}
