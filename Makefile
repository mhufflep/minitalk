.PHONY: all re fclean clean obj_dir

LIBFT_DIR = libft
CLIENT_DIR = client
SERVER_DIR = server

all: libft client server
	@$(MAKE) -f $(LIBFT_DIR) all	
	@$(MAKE) -f $(CLIENT_DIR) all
	@$(MAKE) -f $(SERVER_DIR) all
	
clean:
	@$(MAKE) -f $(LIBFT_DIR) clean
	@$(MAKE) -f $(CLIENT_DIR) clean
	@$(MAKE) -f $(SERVER_DIR) clean

fclean: clean
	@$(MAKE) -f $(LIBFT_DIR) fclean
	@$(MAKE) -f $(CLIENT_DIR) fclean
	@$(MAKE) -f $(SERVER_DIR) fclean

re: fclean all

bonus:

