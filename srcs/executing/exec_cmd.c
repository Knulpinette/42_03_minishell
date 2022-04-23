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
    // if (fd_in != 0)
    // {
    // 	dup2(fd_in, STDIN_FILENO);
    // 	close(fd_in);
    // }
    // if (fd_out != 1)
    // {
    // 	dup2(fd_out, STDOUT_FILENO);
    // 	close(fd_out);
    // }
    // if (valid_command(pipex, 1)) // look into this function
    // 	execve(pipex->cmd_path, pipex->command, pipex->envp); // look into pipex struct
    // error_message(WRONG_CMD); // need to add this
    exit(EXIT_FAILURE); //after execve, if it reaches here there was an issue
}