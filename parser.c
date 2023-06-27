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

    token_list = NULL;
    curr_token = NULL;
    substr = NULL;
    token = NULL;
    i = 0;
    j = 0;
    token_start = 0;
    while (line[i] != '\0' && line[i] != '\n')
    {
        //skip space and tab
        while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
            i++;
        //count how many chars on token
        token_start = i;
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
            i++;
        token_len = i - token_start;

        printf("Token start: %d, Token length: %d\n", token_start, token_len);
        //malloc space to copy str data?????
        substr = malloc(sizeof(char) * (token_len + 1));
        //strncpy(substr, line + token_start, token_len);
        j = 0;
        while (j < token_len)
        {
            substr[j] = line[token_start];
            j++;
            token_start++;
        }
        substr[token_len] = '\0';
        printf("Token substring: %s\n", substr);
        j = 0;
        token = create_token(substr);
        if (token_list == NULL)
        {
            token_list = token;
            curr_token = token;
        }
        else
        {
            curr_token->next = token;
            curr_token = curr_token->next;
        }
        curr_token = token_list;
        while (curr_token)
        {
            printf("substr = %s\n", curr_token->data);
            curr_token = curr_token->next;
        }
        i++;
    }
    return (token_list);
}
