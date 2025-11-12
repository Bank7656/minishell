/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 01:12:09 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 05:12:19 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node  *parse_pipe(t_token **tokens)
{
    t_ast_node  *left_node;
    t_ast_node  *pipe_node;
    t_ast_node  *right_node;

    left_node = parse_subshell(tokens);
    if (left_node == NULL)
        return (NULL);
    while (*tokens != NULL && (*tokens) -> type == PIPE)
    {
        (*tokens) = (*tokens) -> next;
        right_node = parse_subshell(tokens);
        if (right_node == NULL)
        {
            ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
            free_ast_tree(left_node);
            return (NULL);
        }
        pipe_node = (t_ast_node *)malloc(sizeof(t_ast_node));
        if (pipe_node == NULL)
        {
            free_ast_tree(left_node);
            free_ast_tree(right_node);
            return (NULL);
        }
        pipe_node -> left = left_node;
        pipe_node -> right = right_node;
        pipe_node -> type = NODE_PIPE;
        pipe_node -> redir = NULL;
        pipe_node -> args = NULL;
        left_node = pipe_node;
    }
    return (left_node);
}