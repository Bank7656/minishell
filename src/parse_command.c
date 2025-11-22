/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:45:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 01:47:02 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**convert_args_to_array(t_list *arg_list);
t_ast_node	*create_ast_node(t_list *arg_list, t_redir *redir_list);

t_ast_node	*parse_command(t_shell *shell, t_token **tokens)
{
	t_list		*arg_list;
	t_redir		*redir_list;
	t_ast_node	*cmd_node;

	arg_list = NULL;
	redir_list = NULL;
	while (*tokens != NULL && !is_command_end(*tokens))
	{
		if ((*tokens) -> type == WORD)
		{
			if (parse_word(shell, tokens, &arg_list) == 0)
			{
				free_redir_list(redir_list);
				ft_lstclear(&arg_list, free);
				return (NULL);
			}
			*tokens = (*tokens) -> next;
		}
		else if (is_redirection((*tokens) -> type))
		{
			if (parse_redirection(tokens, &redir_list) == 0)
			{
				free_redir_list(redir_list);
				ft_lstclear(&arg_list, free);
				return (NULL);
			}
			(*tokens) = (*tokens) -> next -> next;
		}
	}
	cmd_node = create_ast_node(arg_list, redir_list); 
	if (cmd_node == NULL)
	{
		free_redir_list(redir_list);
		ft_lstclear(&arg_list, free); 
	}
	return (cmd_node);
}

t_ast_node	*create_ast_node(t_list *arg_list, t_redir *redir_list)
{
	t_ast_node *cmd_node;

	cmd_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (cmd_node == NULL)
		return (NULL);
	cmd_node -> type = NODE_COMMAND;
	cmd_node -> args = convert_args_to_array(arg_list);
	if (cmd_node -> args == NULL)
	{
		free(cmd_node);
		return (NULL);
	}
	cmd_node -> redir = redir_list;
	cmd_node -> left = NULL;
	cmd_node -> right = NULL;
	return (cmd_node);
}

char	**convert_args_to_array(t_list *arg_list)
{
	int		i;
	int		len;
	char	**args;
	t_list	*trav_node;

	i = 0;
	len = ft_lstsize(arg_list);
	trav_node = arg_list;
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (args == NULL)
		return (NULL);
	while (trav_node != NULL)
	{
		args[i] = ft_strdup((char *)(trav_node -> content));
		if (args[i] == NULL)
		{
			free_args_array(args);
			return (NULL);
		}
		trav_node = trav_node -> next;
		i++;
	}
	args[i] = NULL;
	ft_lstclear(&arg_list, free);
	return (args);
}
