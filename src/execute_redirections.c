/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 00:55:27 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/16 01:03:23 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirections(t_redir *redir_lst)
{
    int fd;
    t_redir *trav;

    trav = redir_lst;
    while (trav != NULL)
    {
        fd = -1;
    
        if (trav -> type == REDIR_OUT)
            fd = open(trav -> value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (trav -> type == APPEND)
            fd = open(trav -> value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (trav -> type == REDIR_IN)
            fd = open(trav -> value, O_RDONLY, 0644);
        else if (trav -> type == HEREDOC)
            fd = ft_atoi(trav -> value);
    
        if (fd == -1)
        {
            perror("minishell");
            return (-1);
        }
        if (trav -> type == REDIR_IN || trav -> type == HEREDOC)
        {
            if (dup2(fd, STDIN_FILENO) == -1)
                perror("minishell: dup2");
        }
        if (trav -> type == REDIR_OUT || trav -> type == APPEND)
        {
            if (dup2(fd, STDOUT_FILENO) == -1)
                perror("minishell: dup2");
        }
        close(fd);
        trav = trav -> next;
    }
    return (0);
}