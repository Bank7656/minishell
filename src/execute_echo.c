/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:12:30 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 12:11:04 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_option(char *arg);

int execute_echo(t_shell *shell, t_ast_node *node)
{
    int i;
    int is_newline;

    i = 1;
    is_newline = 1;
    while (node -> args[i] != NULL && is_option(node -> args[i]))
    {
        is_newline = 0;
        i++;
    }
    while (node -> args[i] != NULL)
    {
        ft_putstr_fd(node -> args[i], 1);
        if (node -> args[i + 1] != NULL)
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (is_newline == 1)
        ft_putchar_fd('\n', 1);
    return (0);
}

static int  is_option(char *arg)
{
    int i;

    i = 2;
    if (arg == NULL)
        return (0);
    if (arg[0] != '-' || arg[1] != 'n')
        return (0);
    while(arg[i] != '\0')
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}