NAME = minishell

SRC = \
$(addprefix src/, main.c) \
$(addprefix parser/, constructors.c parse.c run.c token.c) \
$(addprefix heredoc/, heredoc.c) \
$(addprefix expansion/, expansion.c expansion_utils.c)
# $(addprefix src/, test_parsing.c parser_visualizer.c)

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
	@$(CC) $(CFLAGS) $(LFLAG) $(OBJ) $(LIBFT) -o $(NAME)

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
