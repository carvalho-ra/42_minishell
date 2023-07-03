#include "minishell.h"

int is_blank(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    else
        return (0);
}

int is_pipe_redir(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    else
        return (0);
}

int single_quote(char *str, int i)
{
    if (str[i] == 39)
    {
        i++;
        while(str[i] && str[i] != 39)
            i++;
        return (i);
    }
    return (i);
}

int double_quote(char *str, int i)
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

t_token *lexer(char *str)
{
    //incluir checagem de pipe e redirect e heredock
    //pode não haver espaço entre as palavras/comandos
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
        while (str[i] && is_blank(str[i]))//is_pipe_redir
            i++;
        start = i;
        while (str[i] && !(is_blank(str[i])))//is_pipe_redir
        {
            i = double_quote(str, i);
            i = single_quote(str, i);
            i++;
            if (is_pipe_redir(str[i - 1]) || is_pipe_redir(str[i]))
                break ;
        }
        if (start != i)
            add_node_bottom(&list, ft_substr(str, start, i - start));
    }
    return (list);
}
