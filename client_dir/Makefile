.PHONY: all re fclean clean obj_dir

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(LIBFT_DIR)

NAME = client

OBJ_DIR = .obj
SRC_DIR = .

LIBFT_DIR = ../libft

HEADERS = client.h utils.h send.h data.h
SOURCES = client.c utils.c send.c data.c
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: obj_dir $(NAME)

obj_dir:
	@if ! [ -d "${OBJ_DIR}" ] ; then mkdir ${OBJ_DIR} ; fi

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -L $(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
