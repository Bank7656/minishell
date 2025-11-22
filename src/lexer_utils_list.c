/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:43:23 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 17:41:20 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_token(t_shell *shell, e_token_type type, char *val);
static void		add_token_to_lst(t_token **head, t_token *token);

int	append_token(t_shell *shell, t_token **head, e_token_type type, char *val)
{
	t_token	*new_token;

	new_token = create_token(shell, type, val);
	if (new_token == NULL)
		return (-1);
	add_token_to_lst(head, new_token);
	return (0);
}

static t_token	*create_token(t_shell *shell, e_token_type type, char *val)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token -> type = type;
	token -> value = ft_strdup(val);
	token -> next = NULL;
	if (token -> value == NULL && val != NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static void	add_token_to_lst(t_token **head, t_token *token)
{
	t_token *trav;
	
	if (*head == NULL)
	{
		*head = token;
	}
	else
	{
		trav = *head;
		while (trav -> next != NULL)
		{
			trav = trav -> next;
		}
		trav -> next = token;
	}
}


void	free_token_list(t_token *head)
{
	t_token	*trav;

	trav = head;
	while (trav != NULL)
	{
		head = head -> next;
		free(trav -> value);
		free(trav);
		trav = head;
	}
}

void	*lexer_error(t_token *head, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(err_msg, 2);
	free_token_list(head);
	return (NULL);
}