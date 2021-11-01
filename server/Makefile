.PHONY: all re fclean clean obj_dir

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ../libft

NAME = server

OBJ_DIR = .obj
SRC_DIR = .

SOURCES = server.c
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: obj_dir $(NAME)

obj_dir:
	@if ! [ -d "${OBJ_DIR}" ] ; then mkdir ${OBJ_DIR} ; fi

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -L ../libft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus:

