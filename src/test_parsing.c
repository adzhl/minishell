#include "../include/minishell.h"

void print_tree(t_cmd *cmd, int depth);

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;
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
			if (cmd_tree)
			{
				print_tree(cmd_tree, 0);
				//run_cmd(cmd_tree);
				//free_tree(cmd_tree); // Assuming free_tree is implemented
			}
			else
			{
				fprintf(stderr, "Error: Parsing failed.\n");
			}
		}
		free(input);
	}
	return (0);
}


// MAIN TO TEST GETTTOKEN
// "ls -l /home/user && echo \"Hello, World!\""
// int main(int ac, char **av)
// {
//     (void) ac; // We won't use the argc

//     char *input = av[1]; // Example input
//     char *ss = input;  // Start of the string (pointer to the first character)
//     char *es = input + strlen(input);  // End of the string (pointer to the last character + 1)

//     char *st, *et;  // To store the start and end of the tokenized substring
//     int token;

//     // We'll keep calling get_token and printing the result until we've processed the entire string
//     while (ss < es)
//     {
//         token = get_token(&ss, es, &st, &et);
//         printf("Token: '%.*s', Start: '%s', End: '%s', Code: %c\n",
//                (int)(et - st), st, st, et, (char)token);

//         // Print more info about the token for debugging
//         // For example, if token represents a symbol or command:
//         if (token == '|')
//             printf("Found pipe symbol '|'\n");
// 		else if (token == '<')
//             printf("Found redirection symbol '<'\n");
// 		else if (token == '>')
//             printf("Found redirection symbol '>'\n");
// 		else if (token == '+')
//             printf("Found redirection symbol '>>'\n");
//         else if (token == '-')
//             printf("Found redirection symbol '<<'\n");
//         else
//             printf("Found something else.\n");
//     }

//     return 0;
// }
