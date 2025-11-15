/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:55:40 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/15 21:17:02 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_list_remove_node(t_env **head, char *name);

int execute_unset(t_shell *shell, t_ast_node *node)
{
    int i;
    int exit_status;
    char    *arg;

    i = 1;
    exit_status = 0;
    while (node -> args[i] != NULL)
    {
        arg = node -> args[i];
        if (check_var_name(arg))
        {
            env_list_remove_node(&shell -> env_lst, arg);
        }
        else
        {
            ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
            exit_status = 1;
        }
        i++;
    }
    return (exit_status);
}

void    env_list_remove_node(t_env **head, char *name)
{
    t_env   *trav;
    t_env   *prev;

    trav = *head;
    prev = NULL;
    while (trav != NULL)
    {
        if (ft_strncmp(trav -> name, name, -1) == 0)
        {
            if (prev == NULL)
                *head = trav -> next;
            else
                prev -> next = trav -> next;
            free(trav -> name);
            free(trav -> value);
            free(trav);
            return ;
        }
        prev = trav;
        trav = trav -> next;
    }
}