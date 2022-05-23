/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osurcouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:44:03 by osurcouf          #+#    #+#             */
/*   Updated: 2022/05/23 10:44:05 by osurcouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Write DEBUG(print_tokens(get_minishell(NULL));) and that line
 * will only be happening if you "make debug"
 
# ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)  
# endif
 */

# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../42_00_libft/libft.h"
# include "colors.h"
# include "struct_def.h"
# include "utils.h"
# include "debug.h"
# include "parsing.h"
# include "builtin_fts.h"
# include "executing.h"

/* INITIALIZER */
t_cmd_table	*init_cmd_table(int nb_cmds);
t_minishell	*init_minishell(char **envp, int argc);

/* INTERFACE */
char		*get_instructions_line(t_mode mode, int fd);

/* SIGNALS */
void		set_signals(t_status status, t_mode mode);
void		set_termcaps(void);

#endif
