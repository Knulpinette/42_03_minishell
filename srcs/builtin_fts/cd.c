#include "minishell.h"

int	cd(t_cmd_table *cmd_table)
{
	t_minishell	*minishell;
	char		*cwd;
	int			i;

	minishell = get_minishell(NULL);
	cwd = NULL;
	cwd = getcwd(cwd, 0); // or without cwd = ?
	chdir(cmd_table->cmd_args[0]); // nops, need to think a lot about this
	i = 0;
	while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "PWD=", 4))
		i++;
	// update PWD in envp with args
	i = 0;
	while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "OLDPWD=", 7))
		i++;
	// update OLDPWD in envp with cwd
	free(cwd);
	return (0); // should be exit code
}
