#ifndef TYPES_H
# define TYPES_H

typedef struct 	s_minishell
{
	char* coconut;
}				t_minishell;

// ask Michele for explanation on how they did it and why
# define EXIT_FILE_NOT_FOUND 127

// error codes that we can use for the error function and making the whole thing clearer.
typedef enum 	e_error_codes
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
}				t_error;


#endif