#include "minishell.h"

t_token *parser(char *line)
{
    t_token *token_list;
    t_token *curr_token;
    t_token *token;
    char *substr;
    int i;
    int line_len;
    int token_start;
    int token_len;

    curr_token = NULL;
    token_list = NULL;
    substr = NULL;
    token = NULL;
    i = 0;
    line_len = strlen(line);
    token_start = 0;
    while (i < line_len)
    {
        //skip space and tab
        while (i < line_len && (line[i] == ' ' || line[i] == '\t'))
            i++;
        if (i >= line_len)
            break ;
        token_start = i;
        //count how many chars on token
        while (i < line_len && line[i] != ' ' && line[i] != '\t')
            i++;
        token_len = i - token_start;
        //malloc space to copy str data?????
        substr = malloc(sizeof(char) * (token_len + 1));
        //strncpy(substr, line + token_start, token_len);
        i = 0;
        while (token_start <= token_len)
        {
            substr[i] = line[token_start];
            token_start++;
            i++;
        }
        substr[token_len] = '\0';
        printf("substr = %s\n", substr);
        token = create_token(substr);

        if (token_list == NULL)
        {
            token_list = token;
            curr_token = token;
        }
        else
        {
            curr_token->next = token_list;
            curr_token = token;
        }
    }
    return (token_list);
}
