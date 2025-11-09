/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 03:07:10 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 16:54:04 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *create_env_node(char **splitted);
void    add_env_to_list(t_env **head, t_env *env_node);

t_env   *init_env(char **envp)
{
	int		i;
	char	**splitted;
    t_env   *env_node;
    t_env   *env_list;

	i = 0;
    env_list = NULL;
	while (envp[i] != NULL)
	{
		splitted = ft_split(envp[i], '='); 
		if (splitted == NULL)
        {
            free_env_list(env_list);
			return (NULL);
        }
        env_node = create_env_node(splitted);
        if (env_node == NULL)
        {
            free_args_array(splitted);
            free_env_list(env_list);
            return (NULL);
        }
        free_args_array(splitted);
        add_env_to_list(&env_list, env_node);  
		i++;
	}
    return (env_list);
}

t_env *create_env_node(char **splitted)
{
    t_env *env_node;

    env_node = (t_env *)malloc(sizeof(t_env));
    if (env_node == NULL)
        return (NULL);
    env_node -> name = ft_strdup(splitted[0]);
    env_node -> value = ft_strdup(splitted[1]);
    if (env_node -> name == NULL || env_node -> value == NULL)
    {
        free(env_node);
        return (NULL);
    }
    env_node -> next = NULL;
    return (env_node);
}

void    add_env_to_list(t_env **head, t_env *env_node)
{
    t_env *trav;
    
    if (*head == NULL)
    {   
        *head = env_node;
    }
    else
    {
        trav = *head;
        while (trav -> next != NULL)
        {
            trav = trav -> next;
        }
        trav -> next = env_node;
    }
}

void free_env_list(t_env *env_list)
{
    t_env *trav;

    trav = env_list;
    while (trav != NULL)
    {
        env_list = env_list -> next;
        free(trav -> name);
        free(trav -> value);
        free(trav);
        trav = env_list;
    }
}
