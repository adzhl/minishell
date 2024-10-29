NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft #-fsanitize=address -g3

LIBFT = libft/libft.a

SRCS =  src/builtin/builtin.c \

OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(LIBFT) :
	make -C libft

clean :
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

.PHONY : all clean fclean re