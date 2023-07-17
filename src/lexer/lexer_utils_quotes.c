#include "../../inc/minishell.h"

int	ft_single_quote(char *str, int i)
{
	if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
			i++;
		return (i);
	}
	return (i);
}

int	ft_double_quote(char *str, int i)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] != '\0' && str[i] != 34)
			i++;
		return (i);
	}
	return (i);
}
