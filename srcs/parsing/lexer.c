#include "minishell.h"

void	lexer(char *line)
{
	t_minishell	*minishell;
	int	i;

	minishell = get_minishell(NULL);
	minishell->instructions = ft_split(line, PIPE);
	minishell->nb_cmd = get_array_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmd);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (ft_strchr(minishell->instructions[i], '>') || ft_strchr(minishell->instructions[i], '<'))
			minishell->cmd_table[i].redirs = 
				get_redirs(minishell->instructions[i], minishell->cmd_table[i].redirs, minishell->cmd_table[i].nb_redirs);
		minishell->cmd_table[i].nb_tokens =
			get_nb_tokens(minishell->instructions[i], SPACE);
		minishell->cmd_table[i].tokens =
			get_tokens(minishell->instructions[i], SPACE, minishell->cmd_table[i].nb_tokens);
		get_tokens_types(minishell->cmd_table[i].tokens, minishell->cmd_table[i].nb_tokens);
		assign_tokens(&minishell->cmd_table[i]);
		DEBUG(print_tokens(minishell->cmd_table[i].tokens, minishell->cmd_table[i].nb_tokens);)
		//DEBUG(printf("cmd = %s\n", minishell->cmd_table[i].cmd_name);)
		//DEBUG(print_split(minishell->cmd_table[i].cmd_args);)

		i++;
	}
	free_split(minishell->instructions);
}

t_cmd_table	*init_cmd_table(int nb_cmd)
{
	t_cmd_table	*cmd_table;
	int			i;

	cmd_table = calloc_or_exit(sizeof(t_cmd_table), nb_cmd + 1);
	i = 0;
	while (i < nb_cmd)
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
