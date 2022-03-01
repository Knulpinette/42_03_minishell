#include "minishell.h"

/*
 * 3 possible situations:
 * 1) no argument is given => change to HOME
 * 2) - => change to OLDPWD
 * 3) relative or absolute path are given => change to path
 * chdir can receive both relative or absolute paths - so smart ✨
 */

int	cd(t_cmd_table *cmd)
{
	t_minishell	*minishell;
	char		*cwd;
	char		*new_cwd;
	int			exit_code;
	int			i;
	extern char	**environ;

	minishell = get_minishell(NULL);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	DEBUG(printf("cwd: %s\n", cwd));
	DEBUG(printf("cmd: %s arg: %s\n", cmd->cmd_name, cmd->cmd_args[0]));
	
	if (!cmd->cmd_args[0])
		new_cwd = getenv("HOME");
	else if (ft_strncmp(cmd->cmd_args[0], "-", 1) == 0)
		new_cwd = getenv("OLDPWD");
	else	
		new_cwd = cmd->cmd_args[0];// nops, need to think a lot about this
	DEBUG(printf("new cwd: %s\n", new_cwd));

	exit_code = chdir(new_cwd); // if exit_code != 0 there's an error
	
	free(cwd);
	cwd = NULL;
	cwd = getcwd(cwd, 0); // to get the absolute path
	printf("cwd after chdir: %s\n", cwd);
	i = 0;
	while (minishell->envp[i] && ft_strncmp(environ[i], "PWD=", 4))
		i++;
	printf("environ %s\n", environ[i]);
	DEBUG(printf("%s\n", getenv("PWD")));	
	// update PWD in envp with args

	DEBUG(printf("%s\n", getenv("OLDPWD")));	
	// update OLDPWD in envp with cwd
	free(cwd);
	return (0); // should be exit code
}
