#include "minishell.h"

void is_history(char *str)
{
    char    *tmp;

    tmp = ft_strtrim(str, " ");
    if (ft_strlen(tmp) != 0 || ft_strlen(str) != 0)
        add_history(str);
}
