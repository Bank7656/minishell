/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:34:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/15 20:09:34 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_env *env_lst, char *key)
{
	t_env *trav;

	trav = env_lst;
	while(trav != NULL)
	{
		if (ft_strncmp(trav -> name, key, -1) == 0)
			return (trav -> value);
		trav = trav -> next;
	}
	return (NULL);
}


char	**convert_env_to_array(t_env *env_lst, int mode)
{
	int		i;
	int		len;
	char	**args;
	char	*temp_str;
	t_env	*trav;

	if (env_lst == NULL)
		return (NULL);
	len = env_lstsize(env_lst);
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	trav = env_lst;
	while (trav != NULL)
	{
        if (trav -> value == NULL && mode == EXPORT)
        {
			args[i] = ft_strdup(trav->name);
			if (args[i] == NULL)
            {
                free_args_array(args);
                return (NULL);
            }
            i++;
        }
        else if (trav -> value != NULL)
        {
            temp_str = ft_strjoin(trav -> name, "=");
            if (temp_str == NULL)
            {
                free_args_array(args);
                return (NULL);
            }
            args[i] = ft_strjoin(temp_str, trav -> value);
            free(temp_str);
            if (args[i] == NULL)
            {
                free_args_array(args);
                return (NULL);
            }  
            i++;
        }
        trav = trav -> next;
	}
	args[i] = NULL;
	return (args);
}

int	env_lstsize(t_env *env_lst)
{
	int	count;

	count = 0;
	while (env_lst != NULL)
	{
		env_lst = env_lst->next;
		count++;
	}
	return (count);
}