/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:43:23 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/05 02:44:11 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


t_token *create_token(e_token_type token_type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("Malloc");
        return (NULL);
    }
    token -> type = token_type;
    token -> value = ft_strdup(value);
    token -> next = NULL;
    if (token -> value == NULL && value != NULL)
    {
        free(token);
        perror("Malloc");
        return (NULL);
    }
    return (token);
}

void    add_token_to_lst(t_token **head, t_token *token)
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


void    free_token_list(t_token *head)
{
    t_token *trav;

    trav = head;
    while (head != NULL)
    {
        head = head -> next;
        free(trav -> value);
        free(trav);
        trav = head;
    }
}

void    *lexer_error(t_token *head, char *err_msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putendl_fd(err_msg, 2);
    free_token_list(head);
    return (NULL);
}