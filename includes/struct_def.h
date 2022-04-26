#ifndef STRUCT_DEF_H
# define STRUCT_DEF_H

/* PARSING MACROS */
# define PROMPT "> "
# define SPACE ' '
# define PIPE '|'
# define SGL_QUOTE '\''
# define DBL_QUOTE '"'

typedef struct s_env {
	char			*name;
	char			*value;
}				t_env;

typedef enum e_token_type
{
	WORD,
	CMD,
	FLAG,
	ENV_VAR,
	REDIR,
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*text;
}				t_token;

typedef enum e_redir_type
{
	OVERWRITE,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_DELIMITER,
	OP_APPEND,
}				t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*arg;
}				t_redir;

typedef struct s_command_table
{
	int				nb_redirs;
	t_redir			*redirs;
	int				nb_tokens;
	t_token			*tokens;
	char			*cmd_name;
	char			**flags;
	char			**cmd_args;
	char			*cmd_path;
	int				fd_in;
	char			*infile;
	int				fd_out;
	t_redir_type	write_mode;
	char			*outfile;
}				t_cmd_table;

/* see
 * https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/
 */
# define EXIT_FILE_NOT_FOUND 127
# define SYNTAX_ERROR 258

/* error codes for personalised error messages */
typedef enum e_error_codes
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
	WRONG_ARGC,
	OPEN_FAIL,
	CLOSE_FAIL,
	PIPE_FAIL,
	WRITE_FAIL,
	WRONG_DIR,
	NO_OLDPWD,
	INVALID_IDENTIFIER,
	REDIR_NO_ARG,
	FORK_FAIL,
	WRONG_CMD
}				t_error;

typedef struct s_minishell
{
	int			nb_cmds;
	char		**instructions;
	t_list		*env;
	char		**env_paths;
	t_cmd_table	*cmd_table;
	int			exit_code;
}				t_minishell;

#endif
