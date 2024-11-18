NAME = minishell

SRC = \
$(addprefix src/, error.c main.c) \
$(addprefix parser/, clean_up.c constructors.c parse.c run_utils.c run.c token.c) \
$(addprefix heredoc/, delimiter.c heredoc.c) \
$(addprefix expansion/, append_utils.c expansion_utils.c expansion.c)

# $(addprefix testing/, parser_visualizer.c tester.c) \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

CC = cc
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
