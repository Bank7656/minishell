/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:34:04 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/28 12:01:36 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	close_pipe(int pipe_fd[2]);

int	execute_pipeline(t_shell *shell, t_ast_node *node)
{
	int		pipe_fd[2];
	int		status;
	int		exit_status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	left_pid = fork();
	if (left_pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (left_pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		exit_status = execute_ast(shell, node->left);
		exit(exit_status);
	}
	right_pid = fork();
	if (right_pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (right_pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe(pipe_fd);
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		exit_status = execute_ast(shell, node->right);
		exit(exit_status);
	}
	close_pipe(pipe_fd);

	
	// waitpid(left_pid, &status, 0);
	// waitpid(right_pid, &status, 0);

	pid_t exit_pid;
	while (true)
	{
		exit_pid = waitpid(-1, &status, 0);
		if (exit_pid == -1)
			break ;
		if (exit_pid == right_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
	}
	return (exit_status);
}

static void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}