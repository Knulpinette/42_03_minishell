#ifndef MINISHELL_H
# define MINISHELL_H

// You can delete that comment once you read it.
// Idea is that with this you can write stuff like DEBUG(print_tokens(get_minishell(NULL));) and that line will only be happening if you "make debug".
// Which is pretty practical I think while we work to verify nothing breaks. Macros are so powerful. It's crazy.
#ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
#endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../42_00_libft/libft.h"
# include "colors.h"
# include "types.h"
# include "utils.h"

#endif

