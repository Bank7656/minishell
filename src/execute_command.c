/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:28:51 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/16 14:28:00 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "cd", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "pwd", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "export", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "unset", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "env", -1) == 0)
        return (1);
    else if (ft_strncmp(cmd, "exit", -1) == 0)
        return (1);
    else
        return (0);
}

int execute_empty_command(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
    int     status;
	int		exit_status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {        
        if (handle_redirections(node -> redir) == -1)
            exit(1);
        exit(0);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
        else
            exit_status = 1;
        return (exit_status);
    }
}

int execute_command(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
    char    *full_path_cmd;
    char    **envp;
    int     status;
	int		exit_status;

    struct sigaction    sa_ignore;
    struct sigaction    sa_prompt;
    struct sigaction    sa_default;
    
    sa_ignore.sa_handler = SIG_IGN;
    sa_prompt.sa_handler = &handle_sigint;
    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_ignore.sa_mask);
    sigemptyset(&sa_prompt.sa_mask);
    sigemptyset(&sa_default.sa_mask);
    sa_ignore.sa_flags = 0;
    sa_prompt.sa_flags = 0;
    sa_default.sa_flags = 0;

    sigaction(SIGINT, &sa_ignore, NULL);
    if (node -> args[0] == NULL)
        return (execute_empty_command(shell, node));
    if (is_builtin(node -> args[0]))
        return (execute_builtin(shell, node));
	pid = fork();
	if (pid == -1)
	{
        perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
        sigaction(SIGINT, &sa_default, NULL);
        sigaction(SIGQUIT, &sa_default, NULL);
        if (handle_redirections(node -> redir) == -1)
        {
            exit(1);
        }
        full_path_cmd = get_full_command_path(node -> args[0], shell -> env_lst);
        if (full_path_cmd == NULL)
        {
            ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->args[0], 2);
			ft_putendl_fd(": command not found", 2);
            exit(127);
        }
        
        envp = convert_env_to_array(shell -> env_lst, ENV);
        if (envp == NULL)
        {
            free(full_path_cmd);
            exit(EXIT_FAILURE);
        }
        if (execve(full_path_cmd, node -> args, envp) == -1)
        {
			perror("execve");
            free_args_array(envp);
            free(full_path_cmd);
            exit(126);
        }
	}
	else
	{
        waitpid(pid, &status, 0);
        sigaction(SIGINT, &sa_prompt, NULL);
		if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
        {
            write(1, "\n", 1);
			exit_status = 128 + WTERMSIG(status);
        }
		else
			exit_status = 1;
		return (exit_status);
	}
    return (-1);
}


char    *get_full_command_path(char *cmd, t_env *env_lst)
{
    int     i;
    char    **env_paths;
    char    *full_cmd_path;

    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    env_paths = get_env_path(env_lst);
    if (env_paths == NULL)
        return (NULL);
    i = 0;
    while (env_paths[i] != NULL)
    {
        full_cmd_path = check_each_path(cmd, env_paths[i]);
        if (full_cmd_path != NULL)
        {
            free(env_paths);
            return (full_cmd_path);
        }
        i++;
    }
    free(env_paths);
    return (NULL);
}

char    *check_each_path(char *cmd, char *path)
{
    char    *temp_path;
    char    *full_path;

    temp_path = ft_strjoin(path, "/");
    if (temp_path == NULL)
        return (NULL);
    full_path = ft_strjoin(temp_path, cmd);
    if (full_path == NULL)
    {
        free(temp_path);
        return (NULL);
    }
    if (access(full_path, X_OK | F_OK) == 0)
        return (full_path);
    free(full_path);
    return (NULL);
}

char    **get_env_path(t_env *env_lst)
{
    char    *path_string;
    char    **split_paths;

    path_string = get_env_value(env_lst, "PATH");
    if (path_string == NULL)
        return (NULL);
    split_paths = ft_split(path_string, ':');
	if (split_paths == NULL)
		return (NULL);
	return (split_paths);
}