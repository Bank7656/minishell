/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:19:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/16 21:22:25by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_str_add_char(char *str, char c);
static char	*expand_dollar_sign(t_shell *shell, char *word, int *i);

char	*expanded_string(t_shell *shell, char *word)
{
	int		i;
	char	quote_state;
	char	*expanded_word;
	char	*full_str;
	char	*temp_str;

	i = 0;
	quote_state = 0;
	temp_str = NULL;
	full_str = ft_strdup("");
	if (full_str == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (word[i] == '\'' && quote_state == 0)
			quote_state = '\'';
		else if (word[i] == '\'' && quote_state == '\'')
			quote_state = 0;
		else if (word[i] == '\"' && quote_state == 0)
			quote_state = '\"';
		else if (word[i] == '\"' && quote_state == '\"')
			quote_state = 0;
		else if (word[i] == '$' && quote_state != '\'')
		{
			expanded_word = expand_dollar_sign(shell, word, &i);
			if (expanded_word == NULL)
			{
				free(full_str);
				return (NULL);
			}
			temp_str = ft_strjoin(full_str, expanded_word);
			free(full_str);
			free(expanded_word);
			full_str = temp_str;
			if (full_str == NULL)
				return (NULL);
			continue ;
		}
		else
		{
			full_str = ft_str_add_char(full_str, word[i]);
			if (full_str == NULL)
				return (NULL);
		}
		i++;
	}
	return (full_str);
}

static char	*ft_str_add_char(char *str, char c)
{
	char	char_str[2];
	char	*new_str;

	char_str[0] = c;
	char_str[1] = '\0';
	new_str = ft_strjoin(str, char_str);
	free(str);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

static char	*expand_dollar_sign(t_shell *shell, char *word, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (word[*i] == '?')
	{
		(*i)++;
		return(ft_itoa(shell -> last_exit_status));
	}
	if (!ft_isalpha(word[*i]) && word[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (word[*i] != '\0' && (ft_isalnum(word[*i]) || word[*i] == '_'))
		(*i)++;
	var_name = ft_substr(word, start, (*i) - start);
	value = get_env_value(shell -> env_lst, var_name);
	free(var_name);
	if (value == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(value));
}
