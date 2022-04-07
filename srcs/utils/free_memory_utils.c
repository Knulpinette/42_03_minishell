#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell->instructions)
		free_split(minishell->instructions);
	if (minishell->cmd_table)
		free_table(minishell->cmd_table, minishell->nb_cmds);
	if (minishell->env)
		ft_lstclear(&minishell->env, &del_env_content);
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

void	free_table(t_cmd_table *cmd_table, int nb_cmds)
{
	int	i;

	i = 0;
	DEBUG(printf("total of cmd to delete = %i\n", nb_cmds);)
	while (i < nb_cmds)
	{
		DEBUG(printf("deleting tokens in cmd_table number %i\n", i);)
		//if (cmd_table[i].redirs)
		//
		//	free(redirs); // change to an actual function del_redir later ! 
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
	DEBUG(printf("total of tokens to delete = %i\n", nb_tokens);)
	while (i < nb_tokens)
	{
		free(tokens[i].text);
		DEBUG(printf("deleting tokens = %i\n", i);)
		i++;
	}
	free(tokens);
}
