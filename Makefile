NAME = minishell

SRC = \
$(addprefix src/, error.c main.c signal.c) \
$(addprefix parser/, clean_up.c constructors.c parse.c run_utils.c run.c token.c) \
$(addprefix heredoc/, delimiter.c heredoc.c) \
$(addprefix expansion/, append_utils.c expansion_utils.c expansion.c) \
$(addprefix builtin/, builtin_cd.c builtin_clear.c builtin_echo.c builtin_env.c builtin_exit.c builtin_export.c builtin_pwd.c builtin_unset.c builtin.c) \
$(addprefix utils/, copy_env.c export_utils.c find_var_name.c free_array.c get_env_value.c update_env_value.c valid_var_name.c exit_status.c find_path.c cmd_error.c)

# $(addprefix testing/, parser_visualizer.c tester.c) \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

CC = cc -g
# compilation flags
CFLAGS = -Wall -Wextra -Werror -Iinclude
# linking flag
LFLAG = -lreadline
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LFLAG)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
