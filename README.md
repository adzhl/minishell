# Minishell

Minishell is a simple shell implementation in C that replicates a subset of the functionality of the Bash shell.
It provides a command-line interface to execute commands, handle pipes, redirections, and built-in commands.

---

## 🚀 Features
- Interactive prompt with history using readline.
- Built-in commands:
  - echo (with -n option)
  - cd (relative/absolute paths)
  - pwd (print working directory)
  - export (add environment variables)
  - unset (remove environment variables)
  - env (print environment variables)
  - exit (exit the shell)
- Supports redirections (<, >, <<, >>) and pipes (|).
- Environment variable expansion ($VAR) and special variable ($? for exit status).
- Handles signals (Ctrl-C, Ctrl-D, Ctrl-\) like Bash in interactive mode.
- Robust parsing for single and double quotes.
- Memory-leak-free custom code.

---

## 🛠️ How to Build
1. Clone the repository:
```bash
git clone https://github.com/adzhl/minishell.git
```
2. Navigate to the project directory:
```bash
cd minishell
   ```
3. Build the program using the Makefile:
```bash
make
```

---

## 📋 Usage
Run the shell:

```bash
./minishell
```
### Example Commands
```bash
$ echo Hello, world!
$ export MY_VAR=42
$ echo $MY_VAR
$ ls -l | grep minishell > output.txt
$ cat << END
This is a here-document.
Type "END" to finish.
END
```

---

## ⚙️ Makefile Targets
- make or make all: Compile the project.
- make clean: Remove object files.
- make fclean: Remove object files and the binary.
- make re: Recompile the entire project.

---

## 🛑 External Functions Used
- readline: Provides a user-friendly command line interface.
- Process Management: fork, execve, wait, pipe, etc.
- File Operations: open, read, write, close, etc.
- Signal Handling: signal, sigaction, etc.

---

## 📚 Dependencies
- Libft: Your custom library for common utility functions.

---

## 🐛 Known Issues
- readline may cause memory leaks (this is acceptable as per the subject).
