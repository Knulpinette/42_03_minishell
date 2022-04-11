#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	print_tokens(t_token *tokens, int words)
{
	int i;

	i = 0;
	while (i < words)
	{
		ft_putstr_fd(tokens[i].text, 2);
		ft_putstr_fd("      ", 2);
		ft_putnbr_fd(tokens[i].type, 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
	return;
}

void	print_redirs(t_redir *redirs, int args)
{
	int i;

	i = 0;
	while (i < args)
	{
		ft_putstr_fd(redirs[i].arg, 2);
		ft_putstr_fd("      ", 2);
		ft_putnbr_fd(redirs[i].type, 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
	return;
}

void	print_debug(void)
{
	t_minishell	*minishell;
	int	i;

	minishell = get_minishell(NULL);
	i = 0;
	printf("\n\n 🥥🌴 "WHITE"COCOSHELLS DEBUG"END_COLOR" 🌴🥥\n");
	printf("_____\n📝 instructions\n");
	printf("🔢 %i\n", minishell->nb_cmds);
	print_split(minishell->instructions);
	while (i < minishell->nb_cmds)
	{
		printf("\n"YELLOW"INSTRUCTION %i"END_COLOR"\n", i + 1);
		printf("_____\n🧭 redirections\n");
		printf("🔢 %i\n", minishell->cmd_table[i].nb_redirs);
		print_redirs(minishell->cmd_table[i].redirs, minishell->cmd_table[i].nb_redirs);
		printf("_____\n🧾 tokens\n");
		printf("🔢 %i\n", minishell->cmd_table[i].nb_tokens);
		print_tokens(minishell->cmd_table[i].tokens, minishell->cmd_table[i].nb_tokens);
		printf("_____\n🎛️ cmd\n");
		if (minishell->cmd_table[i].cmd_name)
			printf("%s\n", minishell->cmd_table[i].cmd_name);
		else
			printf("NO_COMMAND\n");
		printf("_____\n🏳️‍🌈 flags\n");
		if (minishell->cmd_table[i].flags)
			print_split(minishell->cmd_table[i].flags);
		else
			printf("NO_FLAGS\n");
		printf("_____\n📋 cmd_args\n");
		if (minishell->cmd_table[i].cmd_args)
			print_split(minishell->cmd_table[i].cmd_args);
		else
			printf("NO_CMD_ARGUMENTS\n");
		i++;
	}
}
