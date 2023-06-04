#include "minishell.h"

t_token *parser(char *line)
{
    t_token *token;
    t_token *current;
    char *substr;
    int i;
    int line_len;
    int token_start;
    int token_len;

    substr = NULL;
    token = NULL;
    current = token;
    i = 0;
    line_len = strlen(line);
    while (i < line_len)
    {
        //skip space and tab
        while (i < line_len && (line[i] == ' ' || line[i] == '\t'))
            i++;
        if (i >= line_len)
            break ;
        token_start = 0;
        //count how many chars on token
        while (i < line_len || (line[i] != ' ' && line[i] != '\t'))
            i++;
        token_len = i - token_start;
        printf("here");
        //malloc space to copy str data?????
        i = 0;
        while (token_start < token_len)
        {
            substr[i] = line[token_start];
            token_start++;
            i++;
        }
        substr[token_start] = '\0';
        token = create_token(substr);

        if (token == NULL)
        {
            token = token;
            current = token;
        }
        else
        {
            current->next = token;
            current = token;
        }
    }
    return (token);
}