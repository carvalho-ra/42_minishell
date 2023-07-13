#include "minishell.h"

static int	ft_aux_lexer(char *str, int i)
{
	while (str[i] && !(ft_is_blank(str[i])))
	{
		i = ft_double_quote(str, i);
		i = ft_single_quote(str, i);
		i++;
		if (ft_is_pipe_redir(str[i - 1]) || ft_is_pipe_redir(str[i]))
			break ;
	}
	return (i);
}

t_token	*ft_lexer(char *str)
{
	unsigned int i;
	unsigned int start;
	t_token *list;

	list = NULL;
	i = 0;
	start = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_is_blank(str[i]))
			i++;
		start = i;
		i = ft_aux_lexer(str, i);
		if (start != i)
			ft_add_node_bottom(&list, ft_substr(str, start, i - start));
	}
	return (list);
}
