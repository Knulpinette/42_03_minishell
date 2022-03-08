#ifndef BUILTIN_FTS_H
# define BUILTIN_FTS_H

/* CD - Change Directory */
int	cd(t_cmd_table *cmd, t_minishell *minishell);

/* PWD - Print Working Directory */
int	pwd(t_cmd_table *cmd);

/* ENV - print all environment variables */
int	env(t_cmd_table *cmd, t_minishell *minishell);

#endif
