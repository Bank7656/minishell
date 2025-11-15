/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:19:38 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 14:11:24 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_exitcode(const char *str);

int execute_exit(t_shell *shell, t_ast_node *node)
{
    int exit_code;

    if (node -> args[1] == NULL)
        free_and_exit(shell, shell -> last_exit_status);
    if (!is_exitcode(node -> args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
        free_and_exit(shell, 255);
    }
    if (node -> args[2] != NULL)
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
    }
    exit_code = ft_atoi(node -> args[1]) % 256;
    free_and_exit(shell, exit_code);
    return (0);
}

static int  is_exitcode(const char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}