# Minishell

Minishell is a lightweight, interactive shell implementation written in C. It is designed to mimic the core functionalities of bash, providing a functional command-line interface with support for executing commands, managing environments, and handling pipelines and redirections.

## Features

- **Command Execution**: Execute standard system utilities and executables using their absolute/relative paths or via the `$PATH` environment variable.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (with relative/absolute paths)
  - `pwd`
  - `export` (manage environment variables)
  - `unset` (remove environment variables)
  - `env` (display environment variables)
  - `exit` (exit the shell, with exit status support)
- **Pipelines**: Connect the output of one command to the input of another using `|`.
- **Redirections**:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append output redirection (`>>`)
  - Here-document (`<<`)
- **Logical Operators**: Support for `&&` (AND) and `||` (OR) lists for conditional execution of commands.
- **Subshells**: Group commands using parenthesis `()` to run them in an isolated subshell environment.
- **Expansions**:
  - Environment variable expansion (`$VAR`)
  - Exit status of the last command (`$?`)
- **Wildcards**: Support for the `*` wildcard for pattern matching in the current directory.
- **Signal Handling**: Proper handling of `ctrl-C`, `ctrl-D`, and `ctrl-\` mimicking bash's behavior.

## Dependencies

- **GNU Readline library**: Used for command line editing and history management.
  - E.g., via `apt-get install libreadline-dev` on Debian/Ubuntu or `brew install readline` on macOS.
  - **Note for macOS (ARM-based/Apple Silicon) users:** The default or Homebrew-installed readline library might not link or work correctly right now (causing undefined symbol errors like `rl_clear_history` during compilation).
- **C Compiler**: such as `gcc` or `clang` (specified as `cc` in the Makefile).
- **Make**: To build operations.

## Installation & Compilation

1. Clone the repository and navigate into the project directory:
   ```bash
   cd minishell
   ```
2. Build the project using `make`:
   ```bash
   make
   ```
This will compile the source code, along with the included `libft` library, and produce the `minishell` executable.

## Usage

Start the shell by running the compiled executable:

```bash
./minishell
```

You will be presented with a prompt where you can type commands just as you would in bash.

### Examples

```bash
# Simple command
minishell$ ls -l

# Pipeline
minishell$ ls -l | wc -l

# Redirection
minishell$ echo "Hello World" > hello.txt
minishell$ cat < hello.txt

# Logical operators and subshells
minishell$ (echo "Hello" && echo "World") || echo "Failed"

# Environment variables
minishell$ export MY_VAR="minishell is fun"
minishell$ echo $MY_VAR
```

## Makefile Rules

- `make` or `make all`: Compiles the project and generates the executable.
- `make run`: Compiles the project (if necessary) and immediately runs `./minishell`.
- `make clean`: Removes all `.o` object files.
- `make fclean`: Removes all object files and the `minishell` executable.
- `make re`: Performs `fclean` followed by `all` to completely rebuild the project.

## Directory Structure

- `src/`: Contains all the C source files, categorized by their subsystem (lexing, parsing, execution, builtins).
- `include/`: Contains the header files (`minishell.h`, `lexer.h`).
- `libft/`: Contains the custom C library used within the project.
- `objects/`: Directory generated during compilation to store `.o` files.
