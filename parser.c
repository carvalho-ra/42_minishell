#include "minishell.h"

t_token *parser(char *line)
{
    t_token *token_list;
    t_token *curr_token;
    t_token *token;
    char *substr;
    int i;
    int j;
    int token_start;
    int token_len;

    curr_token = NULL;
    token_list = NULL;
    substr = NULL;
    token = NULL;
    i = 0;
    token_start = 0;
    while (line[i])
    {
        //skip space and tab
        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
            i++;
        token_start = i;
        //count how many chars on token
        while (line[i] && line[i] != ' ' && line[i] != '\t')
            i++;
        token_len = i - token_start;
        //malloc space to copy str data?????
        substr = malloc(sizeof(char) * (token_len + 1));
        //strncpy(substr, line + token_start, token_len);
        j = 0;
        while (token_start <= token_len)
        {
            substr[j] = line[token_start];
            token_start++;
            j++;
        }
        substr[token_len] = '\0';
        
        
        token = create_token(substr);
        printf("substr = %s\n", token->data);
        if (token_list == NULL)
        {
            token_list = token;
            curr_token = token;
        }
        else
        {
            curr_token->next = token;
            curr_token = token;
        }
    }
    return (token_list);
}
