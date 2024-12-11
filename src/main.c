/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:37:56 by etien             #+#    #+#             */
/*   Updated: 2024/12/11 09:20:57 by abinti-a         ###   ########.fr       */
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
	char		*input;
	t_cmd		*ast;
	t_mshell	shell;

	((void)argc, (void)argv);
	init_shell(&shell, envp);
	while (1)
	{
		g_signal_received = 0;
		input = readline("minishell$ ");
		if (!input)
			exit_shell();
		if (g_signal_received == SIGINT)
			handle_signal_main(&shell);
		if (*input)
			add_history(input);
		if (syntax_error(input))
			continue ;
		ast = parse_cmd(input, &shell);
		run_cmd_control(input, ast, &shell);
		free_ast(ast);
	}
	free_array(shell.env);
	return (EXIT_SUCCESS);
}

void	init_shell(t_mshell *shell, char **envp)
{
	shell->env = copy_env(envp);
	shell->last_exit_status = 0;
	setup_signal_handling();
}

void	handle_signal_main(t_mshell *shell)
{
	set_exit_status(shell, 130);
	g_signal_received = 0;
}

void	exit_shell(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
