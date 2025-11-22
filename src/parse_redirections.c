/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:36:02 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 13:42:26 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			parse_heredoc(char *delimeter);
static void	parser_print_error(t_token *token);

void	add_redir_back(t_redir **lst, t_redir *new);

int	parse_redirection(t_token **tokens, t_redir **redir_list)
{
	int		heredoc_fd;
	t_redir	*redir_node;

	if ((*tokens) -> next == NULL || (*tokens) -> next -> type != WORD)
	{
		parser_print_error((*tokens) -> next);
		return (0);
	}
	redir_node  = malloc(sizeof(t_redir));
	if (redir_node == NULL)
		return (0);
	redir_node -> type = (*tokens) -> type;
	redir_node -> next = NULL;
	if ((*tokens) -> type == HEREDOC)
	{
		heredoc_fd = parse_heredoc((*tokens) -> next -> value); 
		if (heredoc_fd == -1)
		{
			free(redir_node);
			return (0);
		}
		redir_node -> value = ft_itoa(heredoc_fd);
	}
	else
		redir_node -> value = ft_strdup((*tokens) -> next -> value);
	if (redir_node -> value == NULL)
	{
		free(redir_node);
		return (0);
	}
	add_redir_back(redir_list, redir_node);
	return (1);
}

int	parse_heredoc(char *delimeter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (true)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delimeter, -1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static void	parser_print_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (token == NULL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->value, 2);
	ft_putendl_fd("'", 2);
}



void	add_redir_back(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr -> next != NULL)
	{
		ptr = ptr -> next;
	}
	ptr -> next = new;
	return ;
}