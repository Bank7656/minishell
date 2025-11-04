/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:22:55 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/05 02:32:13 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"




int main(int argc, char **argv, char **envp)
{
    char    *line;

    (void) argc;
    (void) argv;
    (void) envp;
    while (true)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (line[0] == '\0')
            add_history(line);
        // 2. PARSE (Lexer + Parser)
        lexer(line);
        // ast_tree = ???
        
        // 3. EXECUTE
        // execute_ast(ast_tree);

        // 4. CLEANUP
        // free_ast(ast_tree);
        free(line);
    }
    printf("exit\n");
    return (0);
}