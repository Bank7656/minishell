/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:15:17 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 14:02:28 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*create_logical_node(e_token_type type);

t_ast_node	*parse_logical(t_shell *shell, t_token **tokens)
{
	e_token_type	logical;
	t_ast_node		*left_node;
	t_ast_node		*logic_node;
	t_ast_node		*right_node;

	left_node = parse_pipe(shell, tokens);
	if (left_node == NULL)
		return (NULL);
	while (*tokens != NULL && ((*tokens) -> type == AND || (*tokens) -> type == OR))
	{
		logical = (*tokens) -> type; 
		(*tokens) = (*tokens) -> next;
		if (*tokens == NULL)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
			free_ast_tree(left_node);
			return (NULL);
		}
		right_node = parse_pipe(shell, tokens);
		if (right_node == NULL)
		{
			free_ast_tree(left_node);
			return (NULL);
		}
		logic_node = create_logical_node(logical);
		if (logic_node == NULL)
		{
			free_ast_tree(left_node);
			free_ast_tree(right_node);
			return (NULL);
		}
		logic_node -> left = left_node;
		logic_node -> right = right_node;
		left_node = logic_node;
	}
	return (left_node);
}

static t_ast_node	*create_logical_node(e_token_type type)
{
	t_ast_node	*logic_node;
	
	logic_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (logic_node == NULL)
		return (NULL);
	if (type == AND)
		logic_node -> type = NODE_AND;
	else if (type == OR)
		logic_node -> type = NODE_OR;
	logic_node -> left = NULL;
	logic_node -> right = NULL;
	logic_node -> redir = NULL;
	logic_node -> args = NULL;
	return (logic_node);
}