/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:52:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 17:16:27 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_pipe_token(t_shell *shell, t_token **head, char *line, int i)
{
	if (line[i + 1] == '|' && line[i + 1] != '\0')
	{
		if (append_token(shell, head, OR, "||") == -1)
			return (-1);
		return (2);
	}
	else
	{
		if (append_token(shell, head, PIPE, "|") == -1)
			return (-1);
		return (1);
	}
}

int	handle_redir_token(t_shell *shell, t_token **head, char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<' && line[i + 1] != '\0')
		{
			if (append_token(shell, head, HEREDOC, "<<") == -1)
				return (-1);
			return (2);
		}
		else
		{
			if (append_token(shell, head, REDIR_IN, "<") == -1)
				return (-1);
			return (1);
		}
	}
	if (line[i + 1] == '>' && line[i + 1] != '\0')
	{
		if (append_token(shell, head, APPEND, ">>") == -1)
			return (-1);
		return (2);
	}
	else
	{
		if (append_token(shell, head, REDIR_OUT, ">") == -1)
			return (-1);
		return (1);
	}
}

int	handle_and_token(t_shell *shell, t_token **head, char *line, int i)
{
	if (line[i + 1] == '&' && line[i + 1] != '\0')
	{
		if (append_token(shell, head, AND, "&&") == -1)
			return (-1);
		return (2);
	} 
	else
	{
		return (0);
	}
}

int	handle_paren_token(t_shell *shell, t_token **head, char *line, int i)
{
	if (line[i] == '(')
	{
		if (append_token(shell, head, LPAREN, "(") == -1)
			return (-1);
		return (1);
	}
	else if (line[i] == ')')
	{
		if (append_token(shell, head, RPAREN, ")") == -1)
			return (-1);
		return (1);
	}
	return (0);
}
