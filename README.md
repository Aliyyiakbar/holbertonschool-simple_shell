# Holberton School - Simple Shell

This repository contains our C implementation of a custom UNIX command line
interpreter for the Holberton School *Simple Shell* project. It focuses on
parsing input, built-ins, PATH resolution, and process execution.

## Requirements

- OS: Ubuntu 20.04 LTS
- Compiler: `gcc`
- Flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Style: Betty
- No memory leaks
- Max 5 functions per file
- All header files should be include guarded
- Manual page: `man_1_simple_shell`

## Builtins

- `exit` - exit the shell (optional status)
- `env` - print the environment
- `setenv` - set an environment variable
- `unsetenv` - unset an environment variable
- `cd` - change directory
- `alias` - define or print aliases
- `help` - show builtin help
- `history` - show command history

## Features

- Interactive prompt `($)` and non-interactive mode
- Execute external commands with `fork`/`execve`
- Search commands in `PATH`
- Operators: `;`, `&&`, `||`
- Comments with `#` at the start of a token or after whitespace
- Variable expansion: `$?`, `$$`, and `$NAME`
- Alias expansion with a recursion guard
- History stored in `~/.simple_shell_history`
- Script/file mode: `./hsh filename`
- `Ctrl+C` prints a new prompt without exiting

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

Interactive:

```bash
$ ./hsh
($) /bin/ls
file1 file2 file3
($) exit
```

Non-interactive:

```bash
$ echo "/bin/ls" | ./hsh
file1 file2 file3
```

File mode:

```bash
$ ./hsh script.sh
```

## Author

Aliyyiakbar Shirinli  
Nahid Agazadeh
