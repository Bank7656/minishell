/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 01:12:09 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/23 01:23:11 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right);

t_ast_node	*parse_pipe(t_shell *shell, t_token **tokens)
{
	t_ast_node	*left_node;
	t_ast_node	*pipe_node;
	t_ast_node	*right_node;

	left_node = parse_subshell(shell, tokens);
	if (left_node == NULL)
		return (NULL);
	while (*tokens != NULL && (*tokens) -> type == PIPE)
	{
		(*tokens) = (*tokens) -> next;
		if (*tokens == NULL || (*tokens) -> type == PIPE)
		{
			parse_print_error(*tokens);
			shell -> last_exit_status = 2;
			free_ast_tree(left_node);
			return (NULL);
		}
		right_node = parse_subshell(shell, tokens);
		if (right_node == NULL)
		{
			free_ast_tree(left_node);
			return (NULL);
		}
		pipe_node = create_pipe_node(left_node, right_node);
		if (pipe_node == NULL)
		{
			free_ast_tree(left_node);
			free_ast_tree(right_node);
			return (NULL);
		}
		pipe_node -> type = NODE_PIPE;
		left_node = pipe_node;
	}
	return (left_node);
}

static t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (pipe_node == NULL)
		return (NULL);
	pipe_node -> left = left;
	pipe_node -> right = right;
	pipe_node -> args = NULL;
	pipe_node -> redir = NULL;
	return (pipe_node);
}
