/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 02:06:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 02:37:11 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_ast(t_ast_node *node, t_env **env_lst)
{
	int exit_code;

	if (node == NULL)
		return (0);
	else if (node -> type == NODE_COMMAND)
		exit_code = execute_command(node, env_lst);
    else if (node -> type == NODE_PIPE)
        exit_code = execute_pipeline(node, env_lst);
    else if (node -> type == NODE_AND)
    {
        exit_code = execute_ast(node -> left, env_lst);
        if (exit_code == 0)
            exit_code = execute_ast(node -> right, env_lst);
    }
    else if (node -> type == NODE_OR)
    { 
        exit_code = execute_ast(node -> left, env_lst);
        if (exit_code != 0)
            exit_code = execute_ast(node -> right, env_lst);
    }
    else if (node -> type == NODE_SUBSHELL)
        exit_code = execute_subshell(node, env_lst);
    return (exit_code);
}







