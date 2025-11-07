/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:39:22 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/08 01:00:57 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *parse_subshell(t_token **tokens)
{
    t_ast_node *node;
    t_ast_node *subshell_node;

    if (*tokens != NULL && (*tokens) -> type == LPAREN)
    {
        *tokens = (*tokens) -> next;
        node = parse_logical(tokens);
        if ((*tokens) == NULL || (*tokens) -> type != RPAREN)
        {
            // display err
            free_ast_tree(node);
            return (NULL);
        }
        *tokens = (*tokens) -> next;
        subshell_node = (t_ast_node *)malloc(sizeof(t_ast_node));
        if (subshell_node == NULL)
        {
            free_ast_tree(node);
            return (NULL);
        }
        subshell_node -> type = NODE_SUBSHELL;
        subshell_node -> left = node;
        subshell_node -> right = NULL;
        subshell_node -> args = NULL;
        subshell_node -> redir = NULL;
        return (subshell_node);
    }
    else
    {
        node = parse_command(tokens);
        if (node == NULL)
        {
            return (NULL);
        }
    }
    return (node);
}