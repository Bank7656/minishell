/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:22:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/08 02:03:54 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"



void    print_token(t_token *token);

int main(int argc, char **argv, char **envp)
{
    char        *line;
    t_token     *token;
    t_token     *head;
    t_ast_node  *ast_tree;

    (void) argc;
    (void) argv;
    (void) envp;
    while (true)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (line[0] != '\0')
            add_history(line);
        // 2. PARSE (Lexer + Parser)
        token = lexer(line);
        head = token;
        ast_tree = parse_logical(&token);
        
        (void)ast_tree;
        // 3. EXECUTE
        // execute_ast(ast_tree);

        // print_token(token);
        // 4. CLEANUP
        free_token_list(head);
        free_ast_tree(ast_tree);
        free(line);
    }
    printf("exit\n");
    return (0);
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