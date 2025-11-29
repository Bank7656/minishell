/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:40:08 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/23 02:42:35 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_path(t_env *env_lst);
static char	*check_each_path(char *cmd, char *path);

char	*get_full_command_path(char *cmd, t_env *env_lst)
{
	int		i;
	char	**env_paths;
	char	*full_cmd_path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	env_paths = get_env_path(env_lst);
	if (env_paths == NULL)
		return (NULL);
	i = -1;
	while (env_paths[++i] != NULL)
	{
		full_cmd_path = check_each_path(cmd, env_paths[i]);
		if (full_cmd_path != NULL)
		{
			free_args_array(env_paths);
			return (full_cmd_path);
		}
	}
	free_args_array(env_paths);
	return (NULL);
}

static char	**get_env_path(t_env *env_lst)
{
	char	*path_string;
	char	**split_paths;

	path_string = get_env_value(env_lst, "PATH");
	if (path_string == NULL)
		return (NULL);
	split_paths = ft_split(path_string, ':');
	if (split_paths == NULL)
		return (NULL);
	return (split_paths);
}

static char	*check_each_path(char *cmd, char *path)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(path, "/");
	if (temp_path == NULL)
		return (NULL);
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (full_path == NULL)
		return (NULL);
	if (access(full_path, X_OK | F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
