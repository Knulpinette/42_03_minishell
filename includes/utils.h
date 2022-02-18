#ifndef UTILS_H
# define UTILS_H

/* Main utils */
t_minishell		*get_minishell(t_minishell *minishell);

/* Memory utils */
void			free_minishell(t_minishell *minishell);
void			free_split(char **split);

/* Error utils */
int				error_and_exit(t_error code);
void			error_message(t_error code);

#endif