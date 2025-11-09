/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 02:27:50 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 14:22:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_shell *shell, t_ast_node *node)
{
    int subshell_pid;
    int exit_status;
    int status;

    subshell_pid = fork();
    if (subshell_pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (subshell_pid == 0)
    {
        exit_status = execute_ast(shell, node -> left);
        exit(exit_status);
    }
    else
    {
        waitpid(subshell_pid, &status, 0);
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            exit_status = 128 + WTERMSIG(status);
        else
            exit_status = 1;
        return (exit_status); 
    }
}