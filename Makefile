NAME = pipex
LIBFT_A = Libft/libft.a
SRC = pipex.c pipex_utils.c pipex_utils1.c
OBJ = $(SRC:.c=.o)
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)

$(LIBFT_A):
	make -C Libft
%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) libft.a
	make clean -C Libft

fclean: clean
	rm -f $(NAME)
	make fclean -C Libft

re: fclean all