/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:39:22 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/23 01:35:53 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*create_subshell_node(e_node_type type, t_ast_node *node);

t_ast_node	*parse_subshell(t_shell *shell, t_token **tokens)
{
	t_ast_node	*node;
	t_ast_node	*subshell_node;

	if (*tokens == NULL)
		return (NULL);
	if ((*tokens) -> type == LPAREN)
	{
		*tokens = (*tokens) -> next;
		node = parse_logical(shell, tokens);
		if (node == NULL)
			return (NULL);
		if ((*tokens) == NULL || (*tokens) -> type != RPAREN)
		{
			// ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			parse_print_error(*tokens);
			free_ast_tree(node);
			return (NULL);
		}
		*tokens = (*tokens) -> next;
		subshell_node = create_subshell_node(NODE_SUBSHELL, node);
		return (subshell_node);
	}
	else
	{
		node = parse_command(shell, tokens);
		if (node == NULL)
		{
			return (NULL);
		}
	}
	return (node);
}

static t_ast_node	*create_subshell_node(e_node_type type, t_ast_node *node)
{
	t_ast_node	*subshell_node;

	subshell_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (subshell_node == NULL)
	{
		perror("malloc");
		free_ast_tree(node);
		return (NULL);
	}
	subshell_node -> type = type;
	subshell_node -> left = node;
	subshell_node -> right = NULL;
	subshell_node -> args = NULL;
	subshell_node -> redir = NULL;
	return (subshell_node);
}
