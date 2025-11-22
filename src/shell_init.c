/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:57:14 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 01:32:22 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_signal_handler(void);

t_shell *init_shell(char **envp)
{
	t_shell *shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell -> env_lst = init_env(envp);
	if (shell -> env_lst == NULL)
		return (NULL);
	shell -> ast_root = NULL;
	shell -> token_head = NULL;
	init_shell_signal_handler();
	return (shell);
}

static void	init_shell_signal_handler(void)
{
	struct sigaction	sa_prompt;
	struct sigaction	sa_ignore;

	sa_prompt.sa_handler = &handle_sigint;
	sigemptyset(&sa_prompt.sa_mask);
	sa_prompt.sa_flags = 0;
	sigaction(SIGINT, &sa_prompt, NULL);
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGQUIT, &sa_ignore, NULL);
}