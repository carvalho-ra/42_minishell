/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:27:53 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/06 23:25:33 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*superbonder;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	superbonder = malloc(1 * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!superbonder)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			superbonder[i] = s1[i];
	while (s2[j] != '\0')
		superbonder[i++] = s2[j++];
	superbonder[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (superbonder);
}
