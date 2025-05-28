NAME = pipex
SRC = pipex.c
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)
clean:
	rm -f $()