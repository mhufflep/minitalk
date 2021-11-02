.PHONY: all re fclean clean obj_dir

LIBFT_DIR = libft
CLIENT_DIR = client_dir
SERVER_DIR = server_dir

all:
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(CLIENT_DIR) all 
	@$(MAKE) -C $(SERVER_DIR) all

	cp ./$(SERVER_DIR)/server ./
	cp ./$(CLIENT_DIR)/client ./
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(CLIENT_DIR) clean
	@$(MAKE) -C $(SERVER_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(CLIENT_DIR) fclean
	@$(MAKE) -C $(SERVER_DIR) fclean

	rm -f server
	rm -f client

bonus: all

re: fclean all
