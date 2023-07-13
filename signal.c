#include "minishell.h"

void ft_handler(int signal)
{
    //use write on fd = 2?
    write(2, "\n", 1);
	if (signal == SIGINT)
	{
        //move cursor down 1 line
		rl_on_new_line ();
        //replace the line by (no char "", 0)
		rl_replace_line ("", 0);
        //make sure readline will exibit entry
		rl_redisplay ();
	}
}
