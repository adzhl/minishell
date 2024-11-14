/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:43:10 by etien             #+#    #+#             */
/*   Updated: 2024/11/14 13:07:59 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// The string returned by readline is dynamically-allocated,
// hence it needs to be freed.

// // TESTER MAIN FOR CLOSED QUOTES
// int main()
// {
// 	char *input;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 		{
// 			if (quotes_are_closed(input))
// 				printf("Quotes are closed.\n");
// 			else
// 				printf("Quotes are unclosed.\n");
// 			free(input);
// 		}
// 	}
// 	return (0);
// }

// // TESTER MAIN FOR DELIMITER EXPANSION
// int main()
// {
// 	char *input;
// 	char *delim;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 		{
// 			delim = remove_delimiter_quotes(input);
// 			printf("%s\n", delim);
// 			free(input);
// 			free(delim);
// 		}
// 	}
// 	return (0);
// }

// // TESTER MAIN FOR HEREDOC
// int main()
// {
// 	char	*input;
// 	char	*heredoc;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 		{
// 			heredoc = handle_heredoc(input);
// 			printf("Heredoc:\n%s", heredoc);
// 			free(input);
// 			free(heredoc);
// 		}
// 	}
// 	return (0);
// }

// TESTER MAIN FOR PARSER
void print_tree(t_cmd *cmd, int depth);

int	main()
{
	char	*input;
	t_cmd	*cmd_tree;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			cmd_tree = parse_cmd(input);
			run_cmd(cmd_tree);
		}
		free(input);
	}
	return (0);
}

// // TESTER MAIN FOR EXPANSION
// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	char	*input;
// 	char	*exp_input;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 		{
// 			add_history(input);
// 			printf("Original input: %s\n", input);
// 			exp_input = expand_argument(input);
// 			if (exp_input)
// 			{
// 				printf("Expanded input: %s\n", exp_input);
// 				free(exp_input); // Free after using it
// 			}
// 			else
// 				printf("Error expanding variable\n");
// 		}
// 		free(input);
// 	}
// 	return (0);
// }

// ORIGINAL MAIN IMPORTED FROM MY GIT REPO
// // The string returned by readline is dynamically-allocated,
// // hence it needs to be freed.
// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	char	*input;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (input == NULL)
// 			break ;
// 		if (*input)
// 		{
// 			add_history(input);
// 			char	*input_file = "lala.txt";
// 			char	*output_file = "hello.txt";
// 			if (open_fd_main(input_file, output_file))
// 			{
// 				free(input);
// 				continue ;
// 			}
// 			pid_t	pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("Fork failed");
// 				free(input);
// 				continue;
// 			}
// 			else if (pid == 0)
// 			{
// 				char	*args[] = {"/bin/ls", NULL};
// 				execve(args[0], args, NULL);
// 				perror("Execve failed");
// 				exit(1);
// 			}
// 			int	status;
// 			waitpid(pid, &status, 0);
// 		}
// 		printf("Input from user: %s\n", input);
// 		free(input);
// 	}
// 	return (0);
// }

// int open_fd(char *input_file, char *output_file)
// {
// 	int	fd_in = -1;
// 	int	fd_out = -1;

// 	if (input_file)
// 	{
// 		fd_in = open(input_file, O_RDONLY);
// 		if (fd_in < 0)
// 		{
// 			perror("trouble opening input file");
// 			return (-1);
// 		}
// 		dup2(fd_in, STDIN_FILENO);
// 		close(fd_in);
// 	}
// 	if (output_file)
// 	{
// 		fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd_out < 0)
// 		{
// 			perror("trouble opening output file");
// 			return (-1);
// 		}
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_out);
// 	}
// 	return (0);
// }
