#include "../include/minishell.h"

// Function to print command details based on type
void print_tree(t_cmd *cmd, int depth) {
    if (!cmd) return;

    // Indentation based on depth level
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Check type and print accordingly
    if (cmd->type == PIPE) {
        t_pipe_cmd *pipe_cmd = (t_pipe_cmd *)cmd;
        printf("Pipe\n");
        print_tree(pipe_cmd->left, depth + 1);
        print_tree(pipe_cmd->right, depth + 1);
    }
    else if (cmd->type == EXEC) {
        t_exec_cmd *exec_cmd = (t_exec_cmd *)cmd;
        printf("Exec\n");

        // Print each argument in exec command
        for (int i = 0; exec_cmd->argv[i]; i++) {
            for (int j = 0; j < depth + 1; j++) printf("  "); // Indent args
            printf("Arg[%d]: %s\n", i, exec_cmd->argv[i]);
        }
    }
    else if (cmd->type == REDIR) {
        t_redir_cmd *redir_cmd = (t_redir_cmd *)cmd;
        printf("Redir (fd=%d, mode=%d)\n", redir_cmd->fd, redir_cmd->mode);

		// Check for heredoc first, otherwise use file
        for (int i = 0; i < depth + 1; i++) printf("  ");
        if (redir_cmd->heredoc) {
            printf("Heredoc: %s\n", redir_cmd->heredoc);
        } else if (redir_cmd->file) {
            printf("File: %s\n", redir_cmd->file);
        }

        // Print nested command in redirection
        print_tree(redir_cmd->cmd, depth + 1);
    }
}
