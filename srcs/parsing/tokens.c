#include "minishell.h"

/*

ONGOING 

// go with t_tokens or t_list ? 

Parsing tokens
{
	while (instructions)
	{
		if SNG_QUOTE || DBLE_QUOTE
			check_for_a_second_one();
				if (true)
					get_text_in_between_as_string();
	}
}
*/

char	**tokenise(const char *s, char c)
{
	int		words;
	char	**tokens;
	char	*temp;
	int		i;
	int		word;
	int		letters;

	if (!s)
		return (NULL);
	tokens = NULL;
	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		while (s[i + letters] && s[i + letters] != c)
			letters++;
		temp = calloc_or_exit(sizeof(char), (letters + 1));
		letters = 0;
		while (s[i] && s[i] != c)
			temp[letters++] = s[i++];
		*tokens = ft_lstnew(temp);
		(token->next);
	}
	tokens[word] = 0;

	return (tokens);
}
