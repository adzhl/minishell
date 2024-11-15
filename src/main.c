/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:37:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/15 16:44:22 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// The main function will prompt the user for a command in a while loop.
// The command will be added to the readline history and then parsed to
// construct the abstract syntax tree (AST).
// A boolean will check the command for the '|' pipe symbol.
// If the command has pipes, run_cmd will help fork child processes and can
// be called straightaway. However, if it is a simple command without
// pipes, a child process will have to be manually forked. This is necessary
// so that control will be returned to the parent process after the child
// terminates and the program will not exit immediately.
// After the command is executed, the AST will be freed and the user will
// be prompted for a new command.
int	main()
{
	char	*input;
	t_cmd	*ast;
	bool	has_pipe;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		ast = parse_cmd(input);
		has_pipe = ft_strchr(input, '|');
		free(input);
		if (has_pipe)
			run_cmd(ast);
		else
		{
			if (fork_and_check() == 0)
			{
				run_cmd(ast);
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
		free_ast(ast);
	}
	return (0);
}
