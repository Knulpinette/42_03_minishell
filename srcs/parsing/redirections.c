#include "minishell.h"

t_redir	*get_redirs(char *instructions)
{
	t_redir	*redirs;

	redirs = calloc_or_exit(sizeof(t_redir), 1);
	redirs->type = OP_REDIR_OUT;
	redirs->arg = "out";
	(void)instructions;
	return (redirs);
}