/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:21:53 by rcarvalh          #+#    #+#             */
/*   Updated: 2022/07/01 11:58:48 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_find_start(char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

static int	ft_find_len(char *s, char found)
{
	int	len;

	len = 0;
	while (s[len] != found && s[len] != 0)
		len++;
	return (len);
}

static int	ft_count_words(char *s, char c)
{
	int	words;
	int	count;

	count = 0;
	words = 0;
	while (count < (int)ft_strlen(s))
	{
		if (s[count] != c)
		{
			words++;
			while (s[count] != c && s[count] != '\0')
				count++;
		}
		count++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	*src;
	char	**new_str;
	int		count_str;
	int		words;
	int		len;

	count_str = 0;
	src = (char *)s;
	words = ft_count_words(src, c);
	new_str = (char **)ft_calloc (words + 1, sizeof(char *));
	if (!new_str)
		return (NULL);
	while (count_str < words)
	{
		src = ft_find_start(src, c);
		len = ft_find_len(src, c);
		new_str[count_str] = ft_substr(src, 0, len);
		src = src + len;
		count_str++;
	}
	return (new_str);
}
