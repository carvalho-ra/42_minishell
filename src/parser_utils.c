#include "../inc/minishell.h"

int	ft_count_pipes(t_token **list)
{
	t_token	*aux;
	int		i;

	aux = *list;
	i = 0;
	while (aux)
	{
		if (aux->data[0] == '|')
			i++;
		aux = aux->next;
	}
	return (i);
}

// pseudocode

// look for expand ($)
// - function to iterate through strings looking for $ (ISSUE! consider $$???)
// - iterate and do it in each node  

int ft_is_expand(char *str)
{
	int	i;
	int	flag;

	while (str[i])
	{
		i = 0;
		flag = 0;
		while (str[i])
		{
			//TODO
			//ISSUE!! if there's more than one expands in the word must expand
			// preciso dormir .....
			if (str[i] == '$' && str[i + 1])
			{
				flag = 1;
				i++;
				while (str[i++] == '$')
					flag++;
				if (flag <= 2)
					printf("is expand %i\n", flag);
			}
			i++;
		}
	}
	return (0);
}