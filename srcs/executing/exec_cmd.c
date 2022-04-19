#include "minishell.h"

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
    else
        return (0);
    return (1);
}

// check if command exists and flags are appropriate with access (check discord)
// swap stdin/out with fd_in/out -> aftert the fork? we don't want to change stdout/in in main process...
// fork and call execve -> how to get exit code from it? (check goncalo tuto)
int exec_system(t_minishell *minishell, t_cmd_table *cmd)
{
    (void)minishell;
    (void)cmd;
    DEBUG(printf("Called a system function\n"));
    return (0);
}