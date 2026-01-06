# Simple Shell

> A simple UNIX command line interpreter written in C for Holberton School.

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Holberton School](https://img.shields.io/badge/Holberton-School-red.svg)](https://www.holbertonschool.fr/)

## 🔧 Technologies Used

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-333333?style=for-the-badge&logo=gnu&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![VS Code](https://img.shields.io/badge/VS_Code-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

## Description

This project is a custom UNIX command-line interpreter built as part of the Holberton School curriculum. The shell replicates the core behavior of `/bin/sh`, allowing users to execute commands, manage processes, and interact with the operating system through a simple prompt.

It supports both interactive mode (typing commands directly) and non-interactive mode (piping commands from files or other programs). Built entirely in C, this project demonstrates fundamental concepts of system programming including process creation, program execution, and environment management.

---

## 📦 Installation & Usage

### Getting Started with Simple Shell

Ready to explore? Follow these steps to get the shell running on your machine!

### Clone the Repository

```bash
git clone https://github.com/victormonnot/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

### Compile the Project

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

**What do these flags do?**

| Flag | Purpose |
|------|---------|
| `-Wall` | Enable all common warnings |
| `-Werror` | Treat warnings as errors |
| `-Wextra` | Enable extra warnings |
| `-pedantic` | Strict ISO C compliance |
| `-std=gnu89` | Use GNU C89 standard |

✅ This ensures the code is clean, bug-free, and follows C89 coding standards!

### Launch the Shell

```bash
./hsh
```

### 🎉 Ready to Explore!

Try running some basic commands:

```bash
$ ls
$ pwd
$ env
$ exit
```

Use `Ctrl + D` to exit the shell gracefully.

---

## Features

- Display a prompt and wait for user input
- Execute commands with arguments
- Handle the PATH environment variable
- Built-in commands: `exit`, `env`
- Handle EOF (Ctrl+D)
- Error handling matching `/bin/sh` behavior

---

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
        
        U -->|"pid > 0 PARENT"| AA["wait attend enfant"]
        AA --> Y
    end

    Y --> A
    Z --> END2[Fin du shell]
```

---

## 📁 Files

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

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env` | Print the current environment |

---

## Examples

```bash
$ ./hsh
$ /bin/ls
builtins.c  executor.c  helpers.c  input.c  main.c  path.c  shell.h  string_utils.c
$ ls -l
total 32
-rw-r--r-- 1 user user 1234 Jan  5 file1.c
$ echo hello world
hello world
$ exit
$
```

---

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

---
## License

This project is part of the Holberton School curriculum.

---

## Authors

This project was created by students at Holberton School. See the [AUTHORS](AUTHORS) file for the full list of contributors and contact email addresses.

---

<p align="center">
  Made by <a href="https://github.com/panmusic"><b>Panaki</b></a> & <a href="https://github.com/victormonnot"><b>Victor</b></a>
</p>
