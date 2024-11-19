/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:37:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/19 11:35:46 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// The main function will prompt the user for input in a while loop.
// The input will be added to the readline history and then checked
// for syntax errors. If there is an error, the program will not do
// anything and will continue prompting the user for input.
// If the input passes the syntax check, it will be parsed to construct
// the abstract syntax tree (AST). The commands will then be executed.
// Finally, the AST will be freed and the loop restarts.
int	main(void)
{
	char	*input;
	t_cmd	*ast;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (syntax_error(input))
			continue ;
		ast = parse_cmd(input);
		run_cmd_control(input, ast);
		free_ast(ast);
	}
	return (EXIT_SUCCESS);
}

// This function will detect for pipe symbols in the input and either
// call run_cmd directly (if there are pipes) or fork a child process
// to run simple commands. run_cmd will fork child processes for PIPE
// nodes, but we will have to fork them manually if the input does not
// contain pipes. This is necessary so that control will be returned to
// the parent process after the child executes the command and terminates.
// It will prevent the program from exiting immediately.
void	run_cmd_control(char *input, t_cmd *ast)
{
	bool	has_pipe;

	has_pipe = ft_strchr(input, '|');
	free(input);
	if (has_pipe)
		run_cmd(ast);
	else
	{
		if (fork() == 0)
		{
			run_cmd(ast);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
}
