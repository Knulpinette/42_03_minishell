#ifndef UTILS_H
# define UTILS_H

/* Main utils */
t_minishell		*get_minishell(t_minishell *minishell);
t_minishell		*init_minishell();
void			*calloc_or_exit(size_t size, int count);

/* Parsing utils */
int				get_nb_split(char **split);
char			*skip_space(char *line);

/* Memory utils */
void			free_minishell(t_minishell *minishell);
void			free_split(char **split);
void			free_table(t_cmd_table **cmd_table);

/* Error utils */
int				error_and_exit(t_error code);
void			error_message(t_error code);

#endif