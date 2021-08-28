.PHONY: all re fclean clean obj_dir

LIBFT_DIR = libft
CLIENT_DIR = client
SERVER_DIR = server
ROOT_DIR = $(shell pwd)

export LIBFT_DIR
export ROOT_DIR

all:
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(CLIENT_DIR) all 
	@$(MAKE) -C $(SERVER_DIR) all
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(CLIENT_DIR) clean
	@$(MAKE) -C $(SERVER_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(CLIENT_DIR) fclean
	@$(MAKE) -C $(SERVER_DIR) fclean

bonus:
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(CLIENT_DIR) bonus
	@$(MAKE) -C $(SERVER_DIR) bonus

re: fclean all
