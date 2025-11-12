/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:22:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/13 05:01:36 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_shell *init_shell(char **envp);
void    print_token(t_token *token);

int main(int argc, char **argv, char **envp)
{
    t_token     *token;
    t_shell     *shell;

    (void) argc;
    (void) argv;
    shell = init_shell(envp);
    while (true)
    {
        shell -> line = readline("> ");
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
        shell -> ast_root = parse_logical(&token);
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
    printf("exit\n");
    free_and_exit(shell, 0);
    return (0);
}

void    free_inloop(t_shell *shell)
{
    if (shell == NULL)
        return ;
    if (shell -> line != NULL)
        free(shell -> line);
    if (shell -> token_head != NULL)
        free_token_list(shell -> token_head);
    if (shell -> ast_root != NULL)
        free_ast_tree(shell -> ast_root);
    shell -> line = NULL;
    shell -> token_head = NULL;
    shell -> ast_root = NULL;
}

void    free_and_exit(t_shell *shell, int exit_code)
{
    if (shell != NULL)
    {
        free_inloop(shell);
        if (shell -> env_lst != NULL)
            free_env_list(shell -> env_lst);
        free(shell);
    }
    exit(exit_code);
}

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
    return (shell);
}


void    print_token(t_token *token)
{
    t_token *trav;

    trav = token;
    while (trav != NULL) 
    {
        printf("[%s]", trav -> value);
        if (trav -> next != NULL)
            printf("->");
        trav = trav -> next;
    }
    printf("\n");
}