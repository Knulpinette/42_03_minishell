#include "minishell.h"

void	parse(char *line)
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
		minishell->cmd_table[i].nb_tokens = get_nb_tokens(minishell->instructions[i], SPACE);
		minishell->cmd_table[i].tokens =
			tokenise(minishell->instructions[i], SPACE, minishell->cmd_table[i].nb_tokens);
		i++;
	}
	free_split(minishell->instructions); 
	return ;
}

t_cmd_table	*init_cmd_table(int nb_cmd)
{
	t_cmd_table	*cmd_table;
	int			i;

	cmd_table = calloc_or_exit(sizeof(t_cmd_table), nb_cmd + 1);
	i = 0;
	while (i < nb_cmd)
	{
		//cmd_table[i] = calloc_or_exit(sizeof(t_cmd_table), 1);
		cmd_table[i].tokens = NULL;
		cmd_table[i].cmd_name = NULL;
		cmd_table[i].flags = NULL;
		cmd_table[i].cmd_path = NULL;
		cmd_table[i].fd_in = STDIN_FILENO;
		cmd_table[i].infile = NULL;
		cmd_table[i].fd_out = STDOUT_FILENO;
		cmd_table[i].outfile = NULL;
		cmd_table[i].delimiter = false;
		cmd_table[i].delim_arg = NULL;
		cmd_table[i].mode = OVERWRITE;
		cmd_table[i].cmd_arg = NULL;
		i++;
	}
	return (cmd_table);
}

static int	quote_word_count(const char *s, char c, char quote, int i)
{
	while (s[i] && s[i] != quote && s[i + 1])
		i++;
	if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
	{
		if (s[i] == quote && s[i + 1])
			i++;
		return (1);
	}
	return (0);
}

int		quote_len(const char *s, char c, char quote, int i)
{
	int i_start;

	i_start = i;
	i++;
	while (s[i] && s[i] != quote && s[i + 1])
		i++;
	if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
	{
		if (s[i] == quote && s[i + 1])
			i++;
	}
	return (i - i_start);
}

int		get_nb_tokens(const char *s, char c)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == SGL_QUOTE && ft_strchr(s, SGL_QUOTE))
		{
			nb = nb + quote_word_count(s, c, SGL_QUOTE, i + 1);
			i = i + quote_len(s, c, SGL_QUOTE, i);
		}
		else if (s[i] == DBL_QUOTE && ft_strchr(s, DBL_QUOTE))
		{
			nb = nb + quote_word_count(s, c, DBL_QUOTE, i + 1);
			i = i + quote_len(s, c, DBL_QUOTE, i);
		}
		else if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
				nb++;
		i++;
	}
	DEBUG(printf("nb_tokens : %i\n", nb);)
	return (nb);
}
