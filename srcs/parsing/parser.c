#include "minishell.h"

void	parse(char *line)
{
	//TOKENISER / LEXER (vocabulary)
	lexer(line);
	//PARSER (grammar)
	//parser();
	//VALIDATION (meaning)
	// validate_meaning();
	return ;
}
