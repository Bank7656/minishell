/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:22:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/09 17:00:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_shell *init_shell(char **envp);
void    print_token(t_token *token);

int main(int argc, char **argv, char **envp)
{
    char        *line;
    t_token     *token;
    t_shell     *shell;

    (void) argc;
    (void) argv;
    shell = init_shell(envp);
    shell -> is_inloop = 1;
    while (true)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (line[0] != '\0')
            add_history(line);
        token = lexer(shell, line);
        shell -> token_head = token;
        shell -> ast_root = parse_logical(&token);

        // Debugging !!
        // print_ast(ast_tree);
        // print_token(head);
        // End Debugging !!

        execute_ast(shell, shell -> ast_root);
        free_shell(shell); 
        free(line);
    }
    shell -> is_inloop = 0;
    free_shell(shell);
    printf("exit\n");
    return (0);
}

void    free_shell(t_shell *shell)
{
    if (shell == NULL)
        return ;
    if (shell -> is_inloop)
    {
        free_token_list(shell -> token_head);
        free_ast_tree(shell -> ast_root);
    }
    else
    {
        free_env_list(shell -> env_lst);
        free(shell);
    }
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