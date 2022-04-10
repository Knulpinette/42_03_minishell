#include "minishell.h"

// deal with -eeeeeeeeeee or -aaaaaaaaaaaaaaaa or see if the executor handles it.
// handle no_cmd.
// handle wrong input ? or is that the executor
/*
wrong cmd are handled by execve (& flags?)
wrong arg / dir etc are handled by the cmd themselves
open quotes are handled as a indefined behaviour (not handle or handled like the program is waiting for the rest)
*/
