/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:52:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 17:23:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int handle_pipe_token(t_shell *shell, t_token **head, char *line, int i)
{
    if (line[i + 1] == '|' && line[i + 1] != '\0')
    {
        add_token_to_lst(head, create_token(shell, OR, "||"));
        return (2);
    }
    else
    {
        add_token_to_lst(head, create_token(shell, PIPE, "|"));
        return (1);
    }
}

int  handle_redir_token(t_shell *shell, t_token **head, char *line, int i)
{
    if (line[i] == '<')
    {
        if (line[i + 1] == '<' && line[i + 1] != '\0')
        {
            add_token_to_lst(head, create_token(shell, HEREDOC, "<<"));
            return (2);
        }
        else
        {
            add_token_to_lst(head, create_token(shell, REDIR_IN, "<"));
            return (1);
        }        
    }
    if (line[i + 1] == '>' && line[i + 1] != '\0')
    {
        add_token_to_lst(head, create_token(shell, APPEND, ">>"));
        return (2);
    }
    else
    {
        add_token_to_lst(head, create_token(shell, REDIR_OUT, ">"));
        return (1);
    }      
}

int  handle_and_token(t_shell *shell, t_token **head, char *line, int i)
{
    if (line[i + 1] == '&' && line[i + 1] != '\0')
    {
        add_token_to_lst(head, create_token(shell, AND, "&&"));
        return (2);
    } 
    else
    {
        return (0);
    }
}

int handle_paren_token(t_shell *shell, t_token **head, char *line, int i)
{
    if (line[i] == '(')
    {
        add_token_to_lst(head, create_token(shell, LPAREN, "(")); 
        return (1);
    }
    else if (line[i] == ')')
    {
        add_token_to_lst(head, create_token(shell, RPAREN, ")")); 
        return (1);
    }  
    return (0);
}