/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:18:14 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 14:24:29 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_and(t_shell *shell, t_ast_node *node)
{
    int exit_code;

    exit_code = execute_ast(shell, node -> left);
    if (exit_code == 0)
        exit_code = execute_ast(shell, node -> right);
    return (exit_code);
}

int execute_or(t_shell *shell, t_ast_node *node)
{
    int exit_code;

    exit_code = execute_ast(shell, node -> left);
    if (exit_code != 0)
        exit_code = execute_ast(shell, node -> right);    
    return (exit_code);
}