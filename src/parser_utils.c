#include "../inc/minishell.h"

int	ft_is_expand(char *str, unsigned int i)
{
	if(!str[i])
		return (i);
	while(str[i])
	{
		if (str[i] == '$')
		{
			i++;
			//should consider $$???
			// what is it?!
			//Sergio recomends we to talk to Bruno, he got it in a recent evaluation 
			if (str[i + 1] == '$' && str[i] == '$')
				i++;
		}
		printf("is expand");
		return (i);
	}
}

//after $ (or $$??) what shoud exactly happen???
//try to pseudocode

//TODO

// test in bash

//TODO

char	*ft_while_word(char *str, unsigned int i)
{
	if(!str[i])
		return (i);
	while (str[i])
	{
		if (ft_isascii(str[i]))
			i++;
	}
	return (i);
}

