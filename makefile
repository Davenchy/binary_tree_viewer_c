CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu89 $(if $(DEBUG),-g)
NAME = binary_tree
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADERS = $(wildcard includes/*.h)

.PHONY: all run clean fclean re

all: $(NAME)

run: all
	@./$(NAME)

$(NAME): $(HEADERS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
