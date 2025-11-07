/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:45:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/08 01:20:37 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_redir_list(t_redir *redir_list);
char    **convert_args_to_array(t_list *arg_list);
int     parse_redirection(t_token **tokens, t_redir **redir_list);
int     parse_word(t_token **tokens, t_list **arg_list);
int     is_redirection(e_token_type type);
static int is_command_end(t_token *token);
t_ast_node *create_ast_node(t_list *arg_list, t_redir *redir_list);
void	add_redir_back(t_redir **lst, t_redir *new);

t_ast_node    *parse_command(t_token **tokens)
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
			if (parse_word(tokens, &arg_list) == 0)
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

t_ast_node *create_ast_node(t_list *arg_list, t_redir *redir_list)
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

int     parse_word(t_token **tokens, t_list **arg_list)
{
	t_list	*node;
	char    *word;

	word = ft_strdup((*tokens) -> value);
	if (word == NULL)
		return (0); 
	node = ft_lstnew(word);
	if (node == NULL)
	{
		free(word);
		return (0);
	}
	ft_lstadd_back(arg_list, node);
	return (1);
}

void    free_redir_list(t_redir *redir_list)
{
    t_redir *trav;

    trav = redir_list;
    while (redir_list != NULL)
    {
        redir_list = redir_list -> next;
        free(trav -> value);
        free(trav);
        trav = redir_list;
    }
}

char    **convert_args_to_array(t_list *arg_list)
{
	int     i;
	int     len;
	char    **args;
	t_list  *trav_node;

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

int     parse_redirection(t_token **tokens, t_redir **redir_list)
{
	t_redir *redir_node;

	if ((*tokens) -> next == NULL || (*tokens) -> next ->type != WORD)
		return (0);
	redir_node  = malloc(sizeof(t_redir));
	if (redir_node == NULL)
		return (0);
	redir_node -> type = (*tokens) -> type;
	redir_node -> value = ft_strdup((*tokens) -> next -> value);
	if (redir_node -> value == NULL)
	{
		free(redir_node);
		return (0);
	}
	redir_node -> next = NULL;
	add_redir_back(redir_list, redir_node);
	return (1);
}

int     is_redirection(e_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC)
		return (1);
	else
		return (0);
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

static int is_command_end(t_token *token)
{
	if (token == NULL)
		return (1);
	else if (token -> type == PIPE)
		return (1);
	else if (token -> type == RPAREN)
		return (1);
	else if (token -> type == AND)
		return (1);
	else if (token -> type == OR)
		return (1);
	else
		return (0);
}