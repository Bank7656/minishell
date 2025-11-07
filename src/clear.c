/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 01:54:43 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/08 01:12:29 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_ast_tree(t_ast_node *node)
{
    if (node == NULL)
        return ;
    free_ast_tree(node -> left);
    free_ast_tree(node -> right);
    if (node -> type == NODE_COMMAND)
    {
        free_args_array(node -> args);
        free_redir_list(node -> redir);
    }
    free(node);
}

void    free_args_array(char **args)
{
    int i;

    i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}