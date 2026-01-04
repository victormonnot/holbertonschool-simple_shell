# Simple Shell

A simple UNIX command line interpreter written in C for Holberton School.

## Description

This project is a basic implementation of a shell that replicates the behavior of `/bin/sh`. It supports both interactive and non-interactive modes.

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
$ ls -la
$ pwd
$ env
$ exit
```

### Non-Interactive Mode

```bash
$ echo "ls -la" | ./hsh
$ cat commands.txt | ./hsh
```

## Features

- Display a prompt and wait for user input
- Execute commands with arguments
- Handle the PATH environment variable
- Built-in commands: `exit`, `env`
- Handle EOF (Ctrl+D)
- Error handling matching `/bin/sh` behavior

## Flowchart

```mermaid
flowchart TD
    subgraph Phase1["Phase 1: Acquisition"]
        A[while status] --> B{Mode interactif?}
        B -->|Oui| C["Afficher prompt $"]
        B -->|Non| D[read_line avec getline]
        C --> D
        D --> E{EOF Ctrl+D ?}
        E -->|Oui| Z[Break et Free mémoire]
        E -->|Non| F{Input vide?}
        F -->|Oui| A
    end

    subgraph Phase2["Phase 2: Tokenisation"]
        F -->|Non| G["split_line avec strtok"]
        G --> H["Créer tableau args"]
        H --> I["ex: ls -l → args[0]=ls, args[1]=-l, args[2]=NULL"]
    end

    subgraph Phase3["Phase 3: Routeur - Analyse Commande"]
        I --> J{Type de commande?}
        
        J -->|BUILT-IN| K{exit ou env?}
        K -->|exit| Z
        K -->|env| L[Afficher variables env]
        L --> Y[Free mémoire]
        
        J -->|Chemin absolu /bin/ls| M[Chemin déjà valide]
        M --> N[Prêt pour EXEC]
        
        J -->|Commande simple ls| O[Chercher dans PATH]
        O --> P["get_path → /usr/bin:/bin:..."]
        P --> Q["Boucle: stat dir + cmd"]
        Q --> R{Trouvé?}
        R -->|Non| S["print_error: not found"]
        S --> Y
        R -->|Oui| N
    end

    subgraph Phase4["Phase 4: Système - Fork"]
        N --> T[fork]
        T --> U{pid?}
        
        U -->|"pid == 0 ENFANT"| V["execve remplace le code"]
        V --> W{Succès?}
        W -->|Non| X["exit 127"]
        W -->|Oui| END1[Programme exécuté]
        
        U -->|"pid > 0 PARENT"| AA["waitpid attend enfant"]
        AA --> Y
    end

    Y --> A
    Z --> END2[Fin du shell]
```

## Files

| File | Description |
|------|-------------|
| `shell.h` | Header file with prototypes and includes |
| `main.c` | Entry point and main shell loop |
| `input.c` | Input reading and parsing functions |
| `executor.c` | Command execution using fork/execve |
| `path.c` | PATH resolution and command search |
| `builtins.c` | Built-in commands (exit, env) |
| `helpers.c` | Helper functions for error handling |
| `string_utils.c` | String manipulation utilities |

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env` | Print the current environment |

## Examples

```bash
$ ./hsh
$ /bin/ls
file1.c  file2.c  shell.h  main.c
$ ls -l
total 32
-rw-r--r-- 1 user user 1234 Jan  4 file1.c
$ echo hello world
hello world
$ exit
$
```

## Error Handling

Errors are displayed in the format:
```
./hsh: <line_number>: <command>: not found
```

Example:
```bash
$ ./hsh
$ qwerty
./hsh: 1: qwerty: not found
$
```

## License

This project is part of the Holberton School curriculum.
