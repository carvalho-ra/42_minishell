#include "../../inc/minishell.h"

int	ft_marcs(t_shell *shell)
{
	ft_marc_redir_in_file(shell);
	ft_marc_redir_out_file(shell);
	ft_marc_append_file(shell);
    ft_marc_cmd(shell);
    ft_marc_args(shell);

	return (0);
}
