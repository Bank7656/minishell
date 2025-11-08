/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:29 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/08 14:58:34 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include "minishell.h" // Your header with all the struct definitions

/**
 * @brief Helper to print indentation to show the tree's depth.
 */
static void	print_indent(int level)
{
	int	i;

	i = 0;
	while (i < level * 2)
	{
		printf(" ");
		i++;
	}
}

/**
 * @brief Helper to print the contents of a char **args array.
 */
static void	print_args_array(char **args, int level)
{
	int	i;

	if (args == NULL)
		return ;
	print_indent(level + 1);
	printf("Args: ");
	i = 0;
	while (args[i] != NULL)
	{
		printf("[%s] ", args[i]);
		i++;
	}
	printf("\n");
}

/**
 * @brief Helper to get the string for a redirection type.
 */
static const char	*get_redir_type_str(e_token_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("?");
}

/**
 * @brief Helper to print the redirection list for a command.
 */
static void	print_redir_list(t_redir *redir, int level)
{
	if (redir == NULL)
		return ;
	print_indent(level + 1);
	printf("Redirs:\n");
	while (redir != NULL)
	{
		print_indent(level + 2);
		printf("%s %s\n", get_redir_type_str(redir->type), redir->value);
		redir = redir->next;
	}
}

/**
 * @brief The main recursive engine for printing the AST.
 */
static void	print_ast_recursive(t_ast_node *node, int level)
{
	// Base Case: If the node is NULL, do nothing.
	if (node == NULL)
		return ;

	// 1. Print the current node's information
	print_indent(level);
	switch (node->type)
	{
		case NODE_COMMAND:
			printf("NODE_COMMAND\n");
			// A command node has args and redirs, so print them.
			print_args_array(node->args, level);
			print_redir_list(node->redir, level);
			break;
		case NODE_PIPE:
			printf("NODE_PIPE (|)\n");
			break;
		case NODE_AND:
			printf("NODE_AND (&&)\n");
			break;
		case NODE_OR:
			printf("NODE_OR (||)\n");
			break;
		case NODE_SUBSHELL:
			printf("NODE_SUBSHELL ()\n");
			break;
	}

	// 2. Recursively print the children (if they exist)
	if (node->left != NULL)
	{
		print_indent(level);
		printf("LEFT:\n");
		print_ast_recursive(node->left, level + 1);
	}
	if (node->right != NULL)
	{
		print_indent(level);
		printf("RIGHT:\n");
		print_ast_recursive(node->right, level + 1);
	}
}

/**
 * @brief Public-facing function to start printing the AST.
 */
void	print_ast(t_ast_node *node)
{
	printf("--- AST Start ---\n");
	print_ast_recursive(node, 0);
	printf("---- AST End ----\n");
}