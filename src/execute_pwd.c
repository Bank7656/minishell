/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 07:55:38 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 08:20:45 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execute_pwd(t_shell *shell, t_ast_node *node)
{
    char    *path;
    char    cwd[1024];

    (void)node;
    (void)shell;
    path = getcwd(cwd, sizeof(cwd));
    if (path == NULL)
    {
        perror("minishell: pwd");
        return (1);
        
    }
    ft_putendl_fd(path, 1);
    return (0);
}