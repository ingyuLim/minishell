# Minishell

The `Minishell` project is part of the 42 school curriculum, challenging students to create a simple Unix shell with basic functionalities. This project aims to improve understanding of processes, signals, file descriptors, and various system calls.

## Overview
The `Minishell` program is designed to provide a basic shell environment with features such as:

- **Command execution**: Executes commands entered by the user with the ability to handle simple commands and their options.
- **Built-in commands**: Supports built-in commands such as `cd`, `echo`, `env`, `export`, `pwd`, `unset` and `exit`.
- **Environment variables**: Manages and modifies the shell's environment variables.
- **Redirection and pipes**: Handles input and output redirection, as well as piping between commands.

## Usage
1. Clone the project:
```bash
git clone <minishell_git_url>
```

2. Navigate to the project directory:
```bash
cd minishell
```

3. Compile the executable:
```bash
make
```

4. Run the program:
```bash
./minishell
```

5. Enter commands in the shell prompt:
```bash
$ ls -l
$ echo "Hello, Minishell!"
$ cd /path/to/directory
$ exit
```

- To clean up object files:
```bash
make clean
```

- To delete all build files:
```bash
make fclean
```

- To clean and rebuild the executable:
```bash
make re
```
