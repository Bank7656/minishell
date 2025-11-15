/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:30:20 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/15 20:06:16 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_array(char **arr);
int		check_var_name(char *str);
void	set_env_value(t_env **env_lst, char *name, char *value);
void	print_env_array(char **arr);

int	execute_export(t_shell *shell, t_ast_node *node)
{
	int		i;
	char	*arg;
	char	**arr;
	char	*is_equal;
	char	*var_name;
	char	*var_value;
	int		exit_status;

	exit_status = 0;
	if (node->args[1] == NULL)
	{
		arr = convert_env_to_array(shell->env_lst, EXPORT);
		if (arr == NULL)
			return (perror("malloc"), 1);
		sort_env_array(arr);
		print_env_array(arr);
		free_args_array(arr);
		return (0);
	}
	i = 1;
	while (node->args[i] != NULL)
	{
		arg = node->args[i];
		is_equal = ft_strchr(arg, '=');
		if (is_equal == NULL)
		{
			var_name = ft_strdup(arg);
			var_value = NULL;
		}
		else
		{
			var_name = ft_substr(arg, 0, is_equal - arg);
			var_value = ft_strdup(is_equal + 1);
		}
		if (check_var_name(var_name))
			set_env_value(&shell->env_lst, var_name, var_value);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			free(var_name);
			free(var_value);
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}


void	set_env_value(t_env **env_lst, char *name, char *value)
{
	t_env	*trav;
	t_env	*new_node;

	trav = *env_lst;
	while (trav)
	{
		if (ft_strncmp(trav->name, name, -1) == 0)
		{
			free(name);
			if (value)
			{
				free(trav->value);
				trav->value = value;
			}
			return ;
		}
		trav = trav->next;
	}
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
    {
        free(name);
        free(value);
        perror("malloc");
        return ;
    }
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	if (*env_lst == NULL)
		*env_lst = new_node;
	else
	{
		trav = *env_lst;
		while (trav->next != NULL)
			trav = trav->next;
		trav->next = new_node;
	}
}

int	check_var_name(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	sort_env_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i + 1] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strncmp(arr[i], arr[j], -1) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_array(char **arr)
{
	int		i;
	char	*value_ptr;
	int		name_len;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		value_ptr = ft_strchr(arr[i], '=');
		if (value_ptr)
		{
			name_len = value_ptr - arr[i];
			write(1, arr[i], name_len);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value_ptr + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(arr[i], 1);
		i++;
	}
}