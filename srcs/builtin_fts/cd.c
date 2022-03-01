#include "minishell.h"

/*
 * 3 possible situations:
 * 1) no argument is given => change to HOME
 * 2) - => change to OLDPWD
 * 3) relative or absolute path are given => change to path
 */

int	cd(t_cmd_table *cmd)
{
	t_minishell	*minishell;
	char		*cwd;
	char		*new_cwd;
	int			i;

	minishell = get_minishell(NULL);
	cwd = NULL;
	cwd = getcwd(cwd, 0); // or without cwd = ?
	DEBUG(printf("cwd: %s\n", cwd));
	DEGUB(printf("arg: %s\n", cmd->cmd_args[0]));
	if (!cmd->cmd_args[0])
	{
		i = 0;
		while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "HOME=", 5))
			i++;
		new_cwd = ft_strdup(minishell->envp[i] + 5);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "-", 1))
	{
		i = 0;
		while (minishell->envp[i] && ft_strncmp(minishell->envp[i], "OLDPWD=", 7))
			i++;
		new_cwd = ft_strdup(minishell->envp[i] + 7);
	}
	else	
		new_cwd = ft_strdup(cmd->cmd_args[0]);// nops, need to think a lot about this
	DEBUG(printf("new cwd: %s\n", new_cwd));
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
	free(new_cwd);
	return (0); // should be exit code
}
