/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osurcouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:46:19 by osurcouf          #+#    #+#             */
/*   Updated: 2022/05/23 10:46:21 by osurcouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check_valid_quote
**
** Here we are checking that the quote we entered is a closed
**	quote and not an open one.
**
*/

char	check_valid_quote(char *text, char quote)
{
	if (ft_strchr((text + 1), quote))
		return (quote);
	return (0);
}

/*
** there_is_quote
**
** We check there is a closed quote in a given string.
**
*/

bool	there_is_quote(char *text, char quote)
{
	int		i;

	i = 0;
	while (text[i])
	{
		if (text[i] == quote && ft_strchr((text + i + 1), quote))
			return (true);
		i++;
	}
	return (false);
}
