/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 02:06:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 08:38:45 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_ast(t_shell *shell, t_ast_node *node)
{
	int exit_code;

    exit_code = 0;
	if (node == NULL)
		return (0);
	else if (node -> type == NODE_COMMAND)
		exit_code = execute_command(shell, node);
    else if (node -> type == NODE_PIPE)
        exit_code = execute_pipeline(shell, node);
    else if (node -> type == NODE_AND)
        exit_code = execute_and(shell, node);
    else if (node -> type == NODE_OR)
        exit_code = execute_or(shell, node);
    else if (node -> type == NODE_SUBSHELL)
        exit_code = execute_subshell(shell, node);
    else
    {
        ft_putendl_fd("minishell: internal error: unknown node type", 2);
        exit_code = 1;
    }
    shell -> last_exit_status = exit_code;
    return (exit_code);
}
