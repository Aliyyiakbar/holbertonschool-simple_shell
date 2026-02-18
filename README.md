# Holberton School – Simple Shell

This repository contains our C implementation of a custom UNIX command line interpreter for the Holberton School *Simple Shell* project. The goal is to understand how a shell works under the hood by handling the command line, parsing arguments, creating processes, and executing programs using system calls.

## Requirements

- OS: Ubuntu 20.04 LTS
- Compiler: gcc
- Flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Style: Betty
- No memory leaks
- Max 5 functions per file
- All header files should be include guarded

## Authorized Functions / System Calls

- `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `printf`, `fprintf`, `vfprintf`, `sprintf`, `putchar`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`, `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`

## Files

- `AUTHORS` — List of contributors
- `man_1_simple_shell` — Manual page for the shell
- `main.h` — Prototypes, structs, and macros
- `shell.c` — Main entry point (loop, prompt, and execution)
- `parser.c` — Command tokenization and string parsing helpers
- `builtins.c` — Implementation of built-in commands (env, exit)
- `path.c` — Handling the PATH environment variable
- `utils.c` — Shared helpers (string manipulation, memory management)

## Features

- Displays a prompt and waits for the user to type a command.
- Creates a child process in which the command is checked.
- Checks for built-ins first, then searches the `PATH`.
- Handles the end of file condition (`Ctrl+D`).
- Handles `Ctrl+C` signal (does not quit the shell).
- Supports both interactive and non-interactive modes.

### Built-in Commands
- `exit` — Exits the shell
- `env` — Prints the current environment variables

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

The shell works in both interactive and non-interactive mode.

### Interactive Mode
Run the executable and type commands at the prompt:

```bash
$ ./hsh
($) /bin/ls
file1 file2 file3
($)
($) exit
```

### Non-Interactive Mode
Pipe commands into the executable:

```bash
$ echo "/bin/ls" | ./hsh
file1 file2 file3
```

## Example

Output mimics the standard `/bin/sh`.

**Standard sh:**
```bash
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
```

**Our hsh:**
```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
```

## Authors

Nahid Agazadeh

Aliyyiakbar Shirinli
