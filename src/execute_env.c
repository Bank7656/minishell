/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:51:20 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/15 20:10:40 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_env(t_shell *shell, t_ast_node *node)
{
    if (node -> args[1] != NULL)
    {
        ft_putstr_fd("minishell: env: '", 2);
        ft_putstr_fd(node -> args[1], 2);
        ft_putendl_fd("': No such file or directory", 2);
        return (127);
    }
    print_env_lst(shell -> env_lst);
    return (0);
}

void    print_env_lst(t_env *env_lst)
{
    t_env   *trav;

    trav = env_lst;
    while (trav != NULL)
    {
        if (trav -> value != NULL)
        {
            ft_putstr_fd(trav -> name, 1);
            ft_putchar_fd('=', 1);
            ft_putendl_fd(trav -> value, 1);
        }
        trav = trav -> next;
    } 
}