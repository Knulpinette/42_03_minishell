#include "minishell.h"

void	parse(char *line)
{
	t_minishell	*minishell;
	int			i;

	minishell = get_minishell(NULL);
	lexer(line);
	i = 0;
	while (i < minishell->nb_cmds)
	{
		get_tokens_types(minishell->cmd_table[i].tokens, minishell->cmd_table[i].nb_tokens);
		assign_tokens(&minishell->cmd_table[i]);

		DEBUG(printf("_____\nprint redirs\n");)
		DEBUG(print_redirs(minishell->cmd_table[i].redirs, minishell->cmd_table[i].nb_redirs);)
		DEBUG(printf("_____\nprint tokens\n");)
		DEBUG(print_tokens(minishell->cmd_table[i].tokens, minishell->cmd_table[i].nb_tokens);)
		DEBUG(printf("_____\n");)
		//DEBUG(printf("cmd = %s\n", cmd_table[i].cmd_name);)
		//DEBUG(print_split(cmd_table[i].cmd_args);)

		i++;
	}
	//PARSER (grammar)
	//parser();
	//VALIDATION (meaning)
	//validate_input();
	return ;
}
