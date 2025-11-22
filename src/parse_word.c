/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 01:34:51 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 01:46:47 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_quoted(char *str);

int	parse_word(t_shell *shell, t_token **tokens, t_list **arg_list)
{
	t_list	*globbed_lst;
	char	*raw_word;
	char	*expanded_word;
	bool	quote_state;

	raw_word = (*tokens) -> value;
	quote_state = is_quoted(raw_word);
	expanded_word = expanded_string(shell, raw_word);
	if (expanded_word == NULL)
		return (0); 
	if (ft_strchr(expanded_word, '*') && !quote_state)
	{
		globbed_lst = wildcard(shell, expanded_word);
		if (globbed_lst != NULL)
		{
			free(expanded_word);
			ft_lstadd_back(arg_list, globbed_lst);
		}
		else
			ft_lstadd_back(arg_list, ft_lstnew(expanded_word));
	}
	else
		ft_lstadd_back(arg_list, ft_lstnew(expanded_word));
	return (1);
}

static bool	is_quoted(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (true);
	return (false);
}
