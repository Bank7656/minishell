/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:52:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/05 02:52:51 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int handle_pipe_token(t_token **head, char *line, int i)
{
    if (line[i + 1] == '|' && line[i + 1] != '\0')
    {
        add_token_to_lst(head, create_token(OR, "||"));
        return (2);
    }
    else
    {
        add_token_to_lst(head, create_token(PIPE, "|"));
        return (1);
    }
}

int  handle_redir_token(t_token **head, char *line, int i)
{
    if (line[i] == '<')
    {
        if (line[i + 1] == '<' && line[i + 1] != '\0')
        {
            add_token_to_lst(head, create_token(HEREDOC, "<<"));
            return (2);
        }
        else
        {
            add_token_to_lst(head, create_token(REDIR_IN, "<"));
            return (1);
        }        
    }
    if (line[i + 1] == '>' && line[i + 1] != '\0')
    {
        add_token_to_lst(head, create_token(APPEND, ">>"));
        return (2);
    }
    else
    {
        add_token_to_lst(head, create_token(REDIR_OUT, ">"));
        return (1);
    }      
}

int  handle_and_token(t_token **head, char *line, int i)
{
    if (line[i + 1] == '&' && line[i + 1] == '\0')
    {
        add_token_to_lst(head, create_token(AND, "&&"));
        return (2);
    } 
    else
    {
        return (0);
    }
}

int handle_paren_token(t_token **head, char *line, int i)
{
    if (line[i] == '(')
    {
        add_token_to_lst(head, create_token(LPAREN, "(")); 
        return (1);
    }
    else if (line[i] == ')')
    {
        add_token_to_lst(head, create_token(RPAREN, ")")); 
        return (1);
    }  
    return (0);
}