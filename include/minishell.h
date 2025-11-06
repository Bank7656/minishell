/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:14:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/06 02:35:19 by thacharo         ###   ########.fr       */
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
	t_list				*redir;
} t_ast_node;


#endif