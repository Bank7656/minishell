/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:25:36 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 13:35:39 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	globbing(t_list **lst, char *d_name);
static bool	is_matching_wildcard(char *pattern, char *filename);

t_list	*wildcard(t_shell *shell, char *pattern)
{
	t_list			*filename_lst;
	DIR				*dir_steam;
	struct dirent	*dir_entry;

	dir_steam = opendir(".");
	if (dir_steam == NULL)
		return (NULL);
	filename_lst = NULL;
	while (true)
	{
		dir_entry = readdir(dir_steam);
		if (dir_entry == NULL)
			break;
		if (dir_entry -> d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (is_matching_wildcard(pattern, dir_entry -> d_name))
		{
			if (!globbing(&filename_lst, dir_entry -> d_name))
			{
				ft_lstclear(&filename_lst, free);
				closedir(dir_steam);
				return (NULL);
			}
		}
	}
	closedir(dir_steam);
	return (filename_lst);
}

static bool	globbing(t_list **lst, char *d_name)
{
	char	*filename;
	t_list	*node;
	
	filename = ft_strdup(d_name);
	if (filename == NULL)
		return (false);
	node = ft_lstnew((void *)filename);
	if (node == NULL)
	{
		free(filename);
		return (false);
	}
	ft_lstadd_back(lst, node);
	return (true);
}

static bool	is_matching_wildcard(char *pattern, char *filename)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '\0')
			return (true);
		while (*filename != '\0')
		{
			if (is_matching_wildcard(pattern + 1, filename))
				return (true);
			filename++;
		}
		return (is_matching_wildcard(pattern + 1, filename));
	}
	if (*pattern == *filename)
		return (is_matching_wildcard(pattern + 1, filename + 1));
	return (false);
}