NAME = pipex
SRC = pipex.c
OBJ = $(SRC:.c=.o)
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) libft.a -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all