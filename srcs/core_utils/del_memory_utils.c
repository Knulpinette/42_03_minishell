#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell->cmd_table)
		free_table(minishell->cmd_table, minishell->nb_cmd);
	if (minishell->envp_paths)
		free_split(minishell->envp_paths);
	if (minishell)
		free(minishell);
	return ;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_table(t_cmd_table *cmd_table, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd_table[i].tokens)
			free_tokens(cmd_table[i].tokens, cmd_table[i].nb_tokens);
		/*if (cmd_table[i].cmd_args)
			free_split(cmd_table[i].cmd_args);*/
		i++;
	}
	free(cmd_table);
}

void	free_tokens(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens + 1)
	{
		free(tokens[i].text);
		i++;
	}
	free(tokens);
}
