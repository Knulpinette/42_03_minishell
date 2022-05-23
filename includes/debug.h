/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osurcouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:43:47 by osurcouf          #+#    #+#             */
/*   Updated: 2022/05/23 10:43:49 by osurcouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	print_split(char **split);
void	print_tokens(t_token *tokens, int words);
void	print_redirs(t_redir *redirs, int args);
void	print_debug(void);

#endif
