#ifndef STRUCT_DEF_H
# define STRUCT_DEF_H

/* PARSING MACROS */
# define PROMPT "> "
# define SPACE ' '
# define PIPE '|'
# define ENV_VAR '$'
# define QUOTE '\''
# define DBL_QUOTE '"'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define DELIMITER "<<" // see if that makes sense eventually
# define APPEND_MODE ">>" // same

typedef struct 	s_tokens
{
	int		type;
	char	*token;
}				t_tokens;

typedef enum	e_token_type
{
	WORD,
	CMD,
	FLAG,
}				t_token_type;

typedef struct 	s_command_table
{
	t_tokens	**tokens; /* array of tokens */
	char		*cmd;
	char		**flags; /* list of flags */
	char		*cmd_path; /* path to be executed */
	int			infile_fd;
	char		*infile;
	int			outfile_fd;
	char		*outfile;
	bool		delimiter;
	char		*delim_arg;
	int			mode; /* OVERWRITE, APPEND */
	char		**cmd_arg; /* array because of execve */

}				t_cmd_table;

typedef	enum	e_redir_mode
{
	OVERWRITE,  /* Default */
	APPEND, 	/* >> */
}				t_redir_mode;

/* see https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/ */
# define EXIT_FILE_NOT_FOUND 127

// error codes that we can use for the error function and making the whole thing clearer.
typedef enum 	e_error_codes
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
	WRONG_ARGC,
	OPEN_FAIL,
}				t_error;

typedef struct 	s_minishell
{
	int			nb_cmd;
	char		**instructions; /* input instructions parsed from pipes */
	char		**envp_paths; // this is the split with all the paths from envp. We only need to get it once in the beginning. It will always be the same for the whole program.
	t_cmd_table	**cmd_table;

}				t_minishell;

#endif
