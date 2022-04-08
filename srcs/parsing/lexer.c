#include "minishell.h"

void	lexer(char *line)
{
	t_minishell	*minishell;
	char		*temp;
	int			i;

	minishell = get_minishell(NULL);
	minishell->instructions = get_instructions(line, PIPE);
	temp = NULL;
	i = 0;
	while (minishell->instructions[i])
	{
		if (ft_strchr(minishell->instructions[i], '$'))
		{
			temp = rewrite_instruction_with_env_var(minishell->instructions[i]);
			free(minishell->instructions[i]);
			minishell->instructions[i] = temp;
		}
		i++;
	}
	minishell->nb_cmds = get_array_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmds);
	get_command_tables(minishell->cmd_table, minishell->nb_cmds, minishell->instructions);
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
		cmd_table[i].cmd_path = NULL;
		cmd_table[i].fd_in = STDIN_FILENO;
		cmd_table[i].infile = NULL;
		cmd_table[i].fd_out = STDOUT_FILENO;
		cmd_table[i].outfile = NULL;
		cmd_table[i].cmd_args = NULL;
		i++;
	}
	return (cmd_table);
}

void	get_command_tables(t_cmd_table *cmd_table, int nb_cmds, char **instructions)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < nb_cmds)
	{
		cmd_table[i].nb_redirs = get_nb_redirs(instructions[i]);
		if (cmd_table[i].nb_redirs)
		{
			cmd_table[i].redirs = get_redirs(instructions[i], cmd_table[i].nb_redirs);
			temp = rewrite_instruction_without_redirs(instructions[i]);
			free(instructions[i]);
			instructions[i] = temp;
		}
		cmd_table[i].nb_tokens =
			get_nb_tokens(instructions[i], SPACE);
		if (!cmd_table[i].nb_tokens)
			error_and_exit(NO_CMD);
		cmd_table[i].tokens =
			get_tokens(instructions[i], SPACE, cmd_table[i].nb_tokens);
		i++;
	}
}
