/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 00:55:27 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/26 22:47:32 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_redirection(e_token_type type, int fd);

int	handle_redirections(t_redir *redir_lst)
{
	int		fd;
	t_redir	*trav;

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
		if (apply_redirection(trav -> type, fd))
		{
			perror("minishell: dup2");
			return (-1);
		}
		trav = trav -> next;
	}
	return (0);
}

static int	apply_redirection(e_token_type type, int fd)
{
	if (type == REDIR_IN || type == HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	if (type == REDIR_OUT || type == APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
	}
	close(fd);
	return (0);
}
