/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:15:35 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/05 02:47:59 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* --- 1. Main Public Function --- */
t_token		*lexer(char *line);

/* --- 2. Error & Cleanup Functions (Public) --- */
void		free_token_list(t_token *head);
void		*lexer_error(t_token *head, char *err_msg);


// From lexer_utils_char.c
int			ft_isspace(int c);
int			ft_ismetacharacter(int c);

// From lexer_utils_list.c
t_token		*create_token(e_token_type token_type, char *value);
void		add_token_to_lst(t_token **head, t_token *token);

// From lexer_handlers.c
int			handle_pipe_token(t_token **head, char *line, int i);
int			handle_redir_token(t_token **head, char *line, int i);
int			handle_and_token(t_token **head, char *line, int i);
int			handle_paren_token(t_token **head, char *line, int i);

// From lexer.c
int			handle_metacharacter(t_token **head, char *line, int i);
int			handle_word(t_token **head, char *line, int i);

#endif