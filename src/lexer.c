/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:20 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 16:01:43 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token  *lexer(t_shell *shell, char *line)
{
	int         i;
	t_token     *head;
	int         len;

	i = 0;
	head = NULL;
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]))
		{
			i++;
		}
		if (line[i] == '\0')
			break;
		len = handle_metacharacter(shell, &head, line, i);
		if (len == 0)
		{
			len = handle_word(shell, &head, line, i);
		}
		if (len == 0)
			return (lexer_error(head, "syntax error"));
		i += len;
	}

	return (head);
}

int  handle_metacharacter(t_shell *shell, t_token **head, char *line, int i)
{
	if (line[i] == '|')
		return (handle_pipe_token(shell, head, line, i));
	else if (line[i] == '<' || line[i] == '>')
		return (handle_redir_token(shell, head, line, i));
	else if (line[i] == '&')
		return (handle_and_token(shell, head, line, i));
	else if (line[i] == '(' || line[i] == ')')
		return (handle_paren_token(shell, head, line, i));
	else
		return (0);
}

int handle_word(t_shell *shell, t_token **head, char *line, int i)
{
	int     start_index;
	char    quote_char;
	char    *word;

	start_index = i;
	if (line[i] == '\'' || line[i] == '\"')
	{
		quote_char = line[i];
		i++;
		while(line[i] != '\0' && line[i] != quote_char)
		{
			i++;
		}
		if (line[i] == '\0')
			return (0);
		i++;
	}
	else
	{
		start_index = i;
		while(line[i] != '\0' && !(ft_isspace(line[i])) && !(ft_ismetacharacter(line[i])))
		{
			i++;
		}
	}
	word = ft_substr(&line[start_index], 0, i - start_index);
	if (word == NULL)
	{
		perror("Malloc");
		return (0);
	}
	add_token_to_lst(head, create_token(WORD, word)); 
    free(word);
	return (i - start_index);
}

