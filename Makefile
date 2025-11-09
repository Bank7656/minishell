NAME = minishell

CC = cc
# CFLAGS = -g -Wall -Wextra -Werror
CFLAGS = -g

SRC_DIR = src/
OBJ_DIR = objects/
HEADER_DIR = include/
LIBFT_DIR := libft/
DATA_DIR := data/

HEADER = minishell.h \
			lexer.h

LIBFT_NAME = libft.a

SRC = main.c \
	lexer.c \
	lexer_handler.c \
	lexer_utils_char.c \
	lexer_utils_list.c \
	parse_command.c \
	parse_pipe.c \
	parse_logical.c \
	parse_subshell.c \
	envp.c \
	envp_utils.c \
	execute.c \
	execute_command.c \
	execute_pipeline.c \
	execute_logical.c \
	execute_subshell.c \
	debug.c \
	clear.c

OBJECTS = $(SRC:.c=.o)

HEADERS = $(addprefix $(HEADER_DIR), $(HEADER))
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJECTS))
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(HEADERS)
		$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -lreadline -lhistory -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

run: $(NAME)
		@./$(NAME)

clean:
		rm -rf $(OBJ_DIR)
		$(MAKE) clean -C $(LIBFT_DIR)

fclean:
		rm -rf $(NAME)
		rm -rf $(OBJ_DIR)
		$(MAKE) fclean -C $(LIBFT_DIR)

watch:
		watch ps -aux

diff:
		$(info The status of the repository, and the volume of per-file changes:)
		@git status
		@git --no-pager diff --stat

re: fclean all

.PHONY: re fclean clean run debug diff all