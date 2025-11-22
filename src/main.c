/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:22:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/22 00:16:27 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

volatile sig_atomic_t g_signal_status = 0;

int main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_shell	*shell;

	(void) argc;
	(void) argv;
	shell = init_shell(envp);
	while (true)
	{
		shell -> line = readline("minishell > ");
		if (g_signal_status == SIGINT)
		{
			shell -> last_exit_status = 128 + SIGINT;
			g_signal_status = 0;
		}
		if (shell -> line == NULL)
			break;
		if (shell -> line[0] != '\0')
			add_history(shell -> line);
		token = lexer(shell, shell -> line);
		shell -> token_head = token;
		if (shell -> token_head == NULL)
		{
			free_inloop(shell);
			continue;
		}
		print_token(shell -> token_head);
		shell -> ast_root = parse_logical(shell, &token);
		if (shell -> ast_root == NULL)
		{
			free_inloop(shell);
			continue ;
		}
		// Debugging !!
		// print_ast(ast_tree);
		// print_token(head);
		// End Debugging !!
		execute_ast(shell, shell -> ast_root);
		free_inloop(shell); 
	}
	ft_putstr_fd("exit\n", 1);
	free_and_exit(shell, 0);
	return (0);
}

void	free_inloop(t_shell *shell)
{
	if (shell == NULL)
		return ;
	if (shell -> line != NULL)
	{
		free(shell -> line);
		shell -> line = NULL;
	}
	if (shell -> token_head != NULL)
	{
		free_token_list(shell -> token_head);
		shell -> token_head = NULL;
	}
	if (shell -> ast_root != NULL)
	{
		free_ast_tree(shell -> ast_root);
		shell -> ast_root = NULL;
	}
}

void	free_and_exit(t_shell *shell, int exit_code)
{
	if (shell != NULL)
	{
		free_inloop(shell);
		if (shell -> env_lst != NULL)
			free_env_list(shell -> env_lst);
		free(shell);
	}
	rl_clear_history();
	exit(exit_code);
}
