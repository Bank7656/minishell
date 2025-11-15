/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:14:15 by thacharo          #+#    #+#             */
/*   Updated: 2025/11/15 21:18:48 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# define ENV 0
# define EXPORT 1
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "../libft/libft.h"

typedef enum
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	LPAREN,
	RPAREN
}   e_token_type;

typedef struct s_token
{
	e_token_type        type;
	char                *value;
	struct s_token      *next;
}   t_token;

typedef enum
{
   NODE_COMMAND,
   NODE_PIPE,
   NODE_AND,
   NODE_OR,
   NODE_SUBSHELL 
} e_node_type;

typedef struct s_redir
{
	e_token_type	type;	
	char			*value;
	struct s_redir  *next;
}	t_redir;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;


typedef struct s_ast_node
{
	e_node_type			type;
	struct s_ast_node	*left;    
	struct s_ast_node	*right;
	char				**args;
	t_redir				*redir;
} t_ast_node;

typedef struct s_shell
{
    char        *line;
	t_token     *token_head;
	t_env       *env_lst;
	t_ast_node  *ast_root;
    int         last_exit_status;
}   t_shell;


t_ast_node      *parse_command(t_token **tokens);
t_ast_node      *parse_subshell(t_token **tokens);
t_ast_node      *parse_pipe(t_token **tokens);
t_ast_node      *parse_logical(t_token **tokens);

t_env			*init_env(char **envp);
char			*get_env_value(t_env *env_lst, char *key);
char            **convert_env_to_array(t_env *env_lst, int mode);
void			free_env_list(t_env *env_list);
int				env_lstsize(t_env *env_lst);
t_env *create_env_node(char **splitted);
void    add_env_to_list(t_env **head, t_env *env_node);

void			free_redir_list(t_redir *redir_list);
void			free_ast_tree(t_ast_node *node);
void			free_args_array(char **args);


char			*get_full_command_path(char *cmd, t_env *env_lst);
char			**get_env_path(t_env *env_lst);
char			*check_each_path(char *cmd, char *path);

int				execute_ast(t_shell *shell, t_ast_node *node);
int				execute_command(t_shell *shell, t_ast_node *node);
int				execute_pipeline(t_shell *shell, t_ast_node *node);
int				execute_and(t_shell *shell, t_ast_node *node);
int				execute_or(t_shell *shell, t_ast_node *node);
int				execute_subshell(t_shell *shell, t_ast_node *node);


int             execute_builtin(t_shell *shell, t_ast_node *node);
int             execute_pwd(t_shell *shell, t_ast_node *node);
int execute_cd(t_shell *shell, t_ast_node *node);
int execute_echo(t_shell *shell, t_ast_node *node);
int execute_exit(t_shell *shell, t_ast_node *node);
int execute_env(t_shell *shell, t_ast_node *node);
int execute_export(t_shell *shell, t_ast_node *node);
int execute_unset(t_shell *shell, t_ast_node *node);

int	check_var_name(char *str);
void    print_env_lst(t_env *env_lst);
void    print_env_array(char **arr);


void            free_inloop(t_shell *shell);
void            free_and_exit(t_shell *shell, int exit_code);

//debug
void	print_ast(t_ast_node *node);

#endif
