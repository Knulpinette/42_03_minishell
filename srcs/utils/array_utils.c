/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osurcouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:46:54 by osurcouf          #+#    #+#             */
/*   Updated: 2022/05/23 10:46:56 by osurcouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get_array_len
**
** Gets the length of a null-terminated array.
*/

int	get_array_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
