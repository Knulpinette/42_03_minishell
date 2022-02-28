#include "minishell.h"

int	cd(t_cmd_table *cmd_table)
{
	t_minishell	*minishell;
	char		*cwd;
	char		*new_cwd;
	int			i;

	minishell = get_minishell(NULL);
	cwd = NULL;
	DEBUG(printf("before calling getcwd\n"));
	cwd = getcwd(cwd, 0); // or without cwd = ?
	DEBUG(printf("before assigning new cwd to %s\n", cmd_table->cmd_args[0]));
	new_cwd = cmd_table->cmd_args[0];// nops, need to think a lot about this
	DEBUG(printf("before changing dir\n"));
	chdir(new_cwd); 
	i = 0;
	while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "PWD=", 4))
		i++;
	printf("%s\n", minishell->envp[i]);	
	// update PWD in envp with args
	i = 0;
	while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "OLDPWD=", 7))
		i++;
	printf("%s\n", minishell->envp[i]);	
	// update OLDPWD in envp with cwd
	free(cwd);
	return (0); // should be exit code
}
