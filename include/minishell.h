/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:14:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/07 21:38:29 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

typedef enum
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	LPAREN,
	RPAREN
}   e_token_type;

typedef struct s_token
{
	e_token_type        type;
	char                *value;
    struct s_token      *next;
}   t_token;

typedef enum
{
   NODE_COMMAND,
   NODE_PIPE,
   NODE_AND,
   NODE_OR,
   NODE_SUBSHELL 
} e_node_type;

typedef struct s_redir
{
	e_token_type	type;	
	char			*value;
    struct s_redir  *next;
}	t_redir;


typedef struct s_ast_node
{
	e_node_type			type;
	struct s_ast_node	*left;    
	struct s_ast_node	*right;
	char				**args;
	t_redir				*redir;
} t_ast_node;


t_ast_node      *parse_command(t_token **tokens);
t_ast_node      *parse_subshell(t_token **tokens);
t_ast_node      *parse_pipe(t_token **tokens);
t_ast_node      *parse_logical(t_token **tokens);

void    free_redir_list(t_redir *redir_list);
void    free_ast_tree(t_ast_node *node);
void    free_args_array(char **args);

#endif