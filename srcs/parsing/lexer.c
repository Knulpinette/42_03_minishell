#include "minishell.h"

/*
** 🦕🌴
**
**	lexer
** 
** The lexer (tokeniser) is divided in a few steps.
**	1. Divide the input line in instructions with pipe '|' as a delimiter.
**	2. Then get the number of instructions to init the command tables.
**	3. Then get the command tables content.
**
** 🌴🥥
*/

t_error	lexer(char *line)
{
	t_minishell	*minishell;
	t_error		exit_code;

	minishell = get_minishell(NULL);
	minishell->instructions = get_instructions(line, PIPE);
	minishell->nb_cmds = get_array_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmds);
	exit_code = get_command_tables(minishell->cmd_table,
					minishell->nb_cmds, minishell->instructions);
	return (exit_code);
}

t_cmd_table	*init_cmd_table(int nb_cmds)
{
	t_cmd_table	*cmd_table;
	int			i;

	cmd_table = calloc_or_exit(sizeof(t_cmd_table), nb_cmds + 1);
	i = 0;
	while (i < nb_cmds)
	{
		cmd_table[i].redirs = NULL;
		cmd_table[i].tokens = NULL;
		cmd_table[i].cmd_name = NULL;
		cmd_table[i].flags = NULL;
		cmd_table[i].cmd_args = NULL;
		cmd_table[i].cmd_path = NULL;
		cmd_table[i].fd_in = STDIN_FILENO;
		cmd_table[i].infile = NULL;
		cmd_table[i].fd_out = STDOUT_FILENO;
		cmd_table[i].outfile = NULL;
		cmd_table[i].write_mode = OVERWRITE;
		i++;
	}
	return (cmd_table);
}

/*
**	get_command_tables (& two helper functions)
**
**	1. Get the redirections ('>', '<', '>>', '<<' and
**		their following argument).
**	2. Then translate the environement variables - if there's any - in the
**		argument except if the operator is '<<'.
**	2. Rewrite the instruction line without the redirections.
**	3. Translate the environement variables - if there's any - in the
**		instruction line. (Effectively, rewrite the instruction line with
**		the real path of the environement variable.)
**	4. Get the tokens with spaces as delimiter.
**
**	If redir->arg is empty, then treat it as a syntax error that will interupt
**	overall execution of the input line.
**
*/

static bool	is_empty(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] != SPACE)
			return (false);
		i++;
	}
	return (true);
}

static char	*rewrite(char **text, int type)
{
	char	*temp;

	if (type == ENV_VAR)
	{
		temp = rewrite_instruction_with_env_var(*text);
		free(*text);
		*text = temp;
	}
	else if (type == REDIR)
	{
		temp = rewrite_instruction_without_redirs(*text);
		free(*text);
		*text = temp;
	}
	return (*text);
}

t_error	get_command_tables(t_cmd_table *cmd_table, int nb_cmds, char **instructions)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb_cmds)
	{
		cmd_table[i].nb_redirs = get_nb_redirs(instructions[i]);
		if (cmd_table[i].nb_redirs)
		{
			cmd_table[i].redirs = get_redirs(instructions[i], cmd_table[i].nb_redirs);
			j = 0;
			while (j < cmd_table[i].nb_redirs)
			{
				if (is_empty(cmd_table[i].redirs[j].arg))
					return (error_and_return(REDIR_NO_ARG, SYNTAX_ERROR));
				if (ft_strchr(cmd_table[i].redirs[j].arg, '$') && 
						cmd_table[i].redirs[j].type != OP_DELIMITER)
					cmd_table[i].redirs[j].arg = rewrite(&cmd_table[i].redirs[j].arg,
													ENV_VAR);
				j++;
			}
			instructions[i] = rewrite(&instructions[i], REDIR);
		}
		if (ft_strchr(instructions[i], '$'))
			instructions[i] = rewrite(&instructions[i], ENV_VAR);;
		cmd_table[i].nb_tokens = get_nb_tokens(instructions[i], SPACE);
		cmd_table[i].tokens = get_tokens(instructions[i],
								SPACE, cmd_table[i].nb_tokens);
		i++;
	}
	return (0);
}
