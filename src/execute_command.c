/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:28:51 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/26 23:06:32 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process(t_shell *shell, t_ast_node *node);

int	execute_empty_command(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (handle_redirections(node -> redir) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else
			exit_status = 1;
		return (exit_status);
	}
}

int	execute_command(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
	char	*full_path_cmd;
	char	**envp;
	int		status;
	int		exit_status;

	struct sigaction	sa_ignore;
	struct sigaction	sa_prompt;
	struct sigaction	sa_default;

	sa_ignore.sa_handler = SIG_IGN;
	sa_prompt.sa_handler = &handle_sigint;
	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_ignore.sa_mask);
	sigemptyset(&sa_prompt.sa_mask);
	sigemptyset(&sa_default.sa_mask);
	sa_ignore.sa_flags = 0;
	sa_prompt.sa_flags = 0;
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	if (node -> args[0] == NULL)
		return (execute_empty_command(shell, node));
	if (is_builtin(node -> args[0]))
		return (execute_builtin(shell, node));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		sigaction(SIGINT, &sa_default, NULL);
		sigaction(SIGQUIT, &sa_default, NULL);
		execute_child_process(shell, node);
	}
	else
	{
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &sa_prompt, NULL);
		exit_status = get_exit_status(status);
		return (exit_status);
	}
	return (-1);
}


static void	execute_child_process(t_shell *shell, t_ast_node *node)
{
	char	*full_path_cmd;
	char	**envp;

	if (handle_redirections(node -> redir) == -1)
		exit(1);
	full_path_cmd = get_full_command_path(node -> args[0], shell -> env_lst);
	if (full_path_cmd == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	envp = convert_env_to_array(shell -> env_lst, ENV);
	if (envp == NULL)
	{
		free(full_path_cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(full_path_cmd, node -> args, envp) == -1)
	{
		perror("execve");
		free_args_array(envp);
		free(full_path_cmd);
		exit(126);
	}
}