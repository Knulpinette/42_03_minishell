#include "minishell.h"

/*
 * 3 possible situations:
 * 1) no argument is given => change to HOME
 * 2) - => change to OLDPWD and print PWD
 * 3) relative or absolute path are given => change to path
 * chdir can receive both relative or absolute paths - so smart ✨
 *
 * Acessing env variables
 * - envp from main
 * - extern char **environ from unistd.h
 * - getenv("VAR_NAME") for the value of a specific variable
 *
 * Error Handling
 * In bash, additional arguments are ignored, if the first argument
 * is correct then the command works properly.
 * In zsh it says "cd: string not in pwd: <first_arg>"
 */

int	env_var_index(char *env_name)
{
	t_minishell	*minishell;
	int			env_name_len;
	int			i;

	minishell = get_minishell(NULL);
	env_name_len = ft_strlen(env_name);
	i = 0;
	while (minishell->envp[i] &&
		ft_strncmp(minishell->envp[i], env_name, env_name_len))
		i++;
	return (i);
}

char	*update_cwd(char *cwd)
{
	if (cwd)
		free(cwd);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	return (cwd);
}

int	cd(t_cmd_table *cmd)
{
	t_minishell	*minishell;
	char		*cwd;
	char		*new_cwd;
	int			exit_code;

	minishell = get_minishell(NULL);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cmd->cmd_args[0])
		new_cwd = getenv("HOME");
	else if (ft_strncmp(cmd->cmd_args[0], "-", 1) == 0)
		new_cwd = getenv("OLDPWD");
	else	
		new_cwd = cmd->cmd_args[0];
	if ((exit_code = chdir(new_cwd)) != 0) 
	{
		free(cwd);
		error_message(WRONG_DIR);
		return (exit_code);
	}
	minishell->envp[env_var_index("OLDPWD")] = ft_strjoin("OLDPWD=", cwd); // free?
	cwd = update_cwd(cwd);
	minishell->envp[env_var_index("PWD")] = ft_strjoin("PWD=", cwd); // free?
	DEBUG(printf("PWD: %s\n", getenv("PWD")));
	DEBUG(printf("OLDPWD: %s\n", getenv("OLDPWD")));	
	free(cwd);
	return (0);
}
