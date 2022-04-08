#ifndef PARSING_H
# define PARSING_H

/* ENVIRONEMENT VARIABLES */
int			get_nb_env_var(char	*text);
int			get_env_var_len(char *text);
char		*get_env_var(char *text, int env_var_len);
int			get_len_instruction(char *instruction, char **env_var);
char		**get_env_var_split(char *instruction);

/* ENVIRONEMENT PATHS */
char		**get_cmd_paths(char **envp);
char		**finish_paths_by_slash(char **raw_paths);

/* INSTRUCTIONS */
char		**get_instructions(const char *s, char c);
char		*rewrite_instruction_with_env_var(char *instruction);

/* LEXER */
void		lexer(char *line);
t_cmd_table	*init_cmd_table(int nb_cmds);
void		get_command_tables(t_cmd_table *cmd_table, int nb_cmds, char **instructions);

/* PARSER */
void		parse(char *line);

/* QUOTES */
char		check_quote(char letter, char quote);
char		check_valid_quote(char *text, char quote);
bool		there_is_quote(char *text, char quote);
int			get_nb_quotes(char *text);
char		*remove_quotes(char *text);

/* REDIRECTIONS */
int			get_nb_redirs(char *instructions);
t_redir		*get_redirs(char *instructions, t_redir *redirs, int nb_redirs);

/* TOKENS */
int			get_nb_tokens(const char *s, char c);
t_token		*get_tokens(const char *s, char c, int words);
/* 	tokens_types */
void		get_tokens_types(t_token *tokens, int nb_tokens);

/* VALIDATION */
void		assign_tokens(t_cmd_table *cmd_table);

#endif