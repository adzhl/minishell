/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:37:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/27 13:44:35 by abinti-a         ###   ########.fr       */
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
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*ast;
	t_mshell shell;

	(void)argc;
	(void)argv;
	while (1)
	{
		shell.env = create_env_copy(envp);
		shell.last_exit_status = 0;
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (syntax_error(input))
			continue ;
		ast = parse_cmd(input);
		run_cmd_control(input, ast, &shell);
		free_ast(ast);
	}
	return (EXIT_SUCCESS);
}
