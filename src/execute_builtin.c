/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 07:56:02 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/26 22:31:06 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *shell, t_ast_node *node)
{
	if (ft_strncmp(node -> args[0], "echo", -1) == 0)
		execute_echo(shell, node);
	else if (ft_strncmp(node -> args[0], "cd", -1) == 0)
		return (execute_cd(shell, node));
	else if (ft_strncmp(node -> args[0], "pwd", -1) == 0)
		return (execute_pwd(shell, node));
	else if (ft_strncmp(node -> args[0], "export", -1) == 0)
		return (execute_export(shell, node));
	else if (ft_strncmp(node -> args[0], "unset", -1) == 0)
		return (execute_unset(shell, node));
	else if (ft_strncmp(node -> args[0], "env", -1) == 0)
		return (execute_env(shell, node));
	else if (ft_strncmp(node -> args[0], "exit", -1) == 0)
		return (execute_exit(shell, node));
	return (1);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", -1) == 0)
		return (1);
	else
		return (0);
}
