/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:19:11 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 13:40:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_end(t_token *token)
{
	if (token == NULL)
		return (1);
	else if (token -> type == PIPE)
		return (1);
	else if (token -> type == RPAREN)
		return (1);
	else if (token -> type == AND)
		return (1);
	else if (token -> type == OR)
		return (1);
	else
		return (0);
}

int	is_redirection(e_token_type type)
{
	if (type == REDIR_IN)
		return (1);
	else if (type == REDIR_OUT)
		return (1);
	else if (type == APPEND)
		return (1);
	else if (type == HEREDOC)
		return (1);
	else
		return (0);
}