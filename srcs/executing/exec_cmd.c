#include "minishell.h"

int is_builtin(char *cmd_name)
{
    if (ft_strncmp(cmd_name, "cd", 2) == 0
        || ft_strncmp(cmd_name, "pwd", 3) == 0
        || ft_strncmp(cmd_name, "env", 3) == 0
        || ft_strncmp(cmd_name, "echo", 4) == 0
        || ft_strncmp(cmd_name, "export", 6) == 0
        || ft_strncmp(cmd_name, "unset", 5) == 0
        || ft_strncmp(cmd_name, "exit", 4) == 0)
        return (1);
    return (0);
}

int exec_builtin(t_minishell *minishell, t_cmd_table *cmd)
{
    if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
        minishell->exit_code = cd(cmd);
    else if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
        minishell->exit_code = pwd(cmd);
    else if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
        minishell->exit_code = env(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
        minishell->exit_code = echo(cmd);
    else if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
        minishell->exit_code = export(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
        minishell->exit_code = unset(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
        printf("EXIT is still not done 😅\n");
    else
        return (0);
    return (1);
}

/*
** Checks if the command exists on each path and is executable
** Access function: F_OK - command exists
**                  X_OK - is executable
** If yes, the path is stored in that cmd_table, ready to be used
*/
int	valid_command(t_minishell *minishell, t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (minishell->envp_paths[i])
	{
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		cmd->cmd_path = ft_strjoin(minishell->envp_paths[i], cmd->cmd_name);
		if (access(cmd->cmd_path, F_OK) == 0
			&& access(cmd->cmd_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

// check if command exists and flags are appropriate with access (check discord)
// swap stdin/out with fd_in/out -> aftert the fork? we don't want to change stdout/in in main process...
// fork and call execve -> how to get exit code from it? (check goncalo tuto)
void exec_system(t_minishell *minishell, t_cmd_table *cmd)
{
    (void)minishell;
    (void)cmd;
    DEBUG(printf("Called a system function\n"));
    // child process:
    // close pipe's reading end? Which is in next cmd fd_in?
    if (comd->fd_in != 0)
    {
    	dup2(comd->fd_in, STDIN_FILENO);
    	close(comd->fd_in);
    }
    if (comd->fd_out != 1)
    {
    	dup2(comd->fd_out, STDOUT_FILENO);
    	close(comd->fd_out);
    }
    //if (valid_command(minishell, cmd)) // What about the flags?
    //    execve(cmd->cmd_path, ARRAY, minishell->envp); // look into pipex struct
    // error_message(WRONG_CMD); // need to add this
    exit(EXIT_FAILURE); //after execve, if it reaches here there was an issue
}

// Why does execve needs envp? Can't really give it ours... :/
// How is execve array? Check CodeVault