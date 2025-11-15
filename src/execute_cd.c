/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 08:41:43 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 08:51:23 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cd(t_shell *shell, t_ast_node *node)
{
    char    *path;

    path = node -> args[1];
    if (node -> args[1] != NULL && node -> args[2] != NULL)
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return (1);
    }
    if (path == NULL)
    {
       path = get_env_value(shell -> env_lst, "HOME"); 
       if (path == NULL)
       {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            return(1);
       }
    }
    if (chdir(path) == -1)  
    {
      perror("minishell: cd");
      return (1);
    }
    return (0);
}