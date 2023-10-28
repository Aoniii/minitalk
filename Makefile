NAME = minitalk
CLIENT = client
SERVER = server
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I includes -fPIE

SRCC = client.c
SRCS = server.c

OBJC = $(SRCC:.c=.o)
OBJS = $(SRCS:.c=.o)

R = \e[38;5;$(shell seq 0 255 | shuf | head -n1)m
RESET = \e[0m

define logo
	clear
	@printf "$(R)"
	@printf "   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█      ███        ▄████████  ▄█          ▄█   ▄█▄\n"
	@printf " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███  ▀█████████▄   ███    ███ ███         ███ ▄███▀ \n"
	@printf " ███   ███   ███ ███▌ ███   ███ ███▌    ▀███▀▀██   ███    ███ ███         ███▐██▀   \n"
	@printf " ███   ███   ███ ███▌ ███   ███ ███▌     ███   ▀   ███    ███ ███        ▄█████▀    \n"
	@printf " ███   ███   ███ ███▌ ███   ███ ███▌     ███     ▀███████████ ███       ▀▀█████▄    \n"
	@printf " ███   ███   ███ ███  ███   ███ ███      ███       ███    ███ ███         ███▐██▄   \n"
	@printf " ███   ███   ███ ███  ███   ███ ███      ███       ███    ███ ███▌    ▄   ███ ▀███▄ \n"
	@printf "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀      ▄████▀     ███    █▀  █████▄▄██   ███   ▀█▀ \n"
	@printf "                                                              ▀           ▀         $(RESET)\n"
endef

all: $(NAME)

$(NAME): $(LIBFT) $(SERVER) $(CLIENT)
	$(call logo)

$(LIBFT): 
	@$(MAKE) -C libft/

$(SERVER): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(SERVER)

$(CLIENT): $(OBJC)
	@gcc $(CFLAGS) $(OBJC) $(LIBFT) -o $(CLIENT)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJC)
	@$(MAKE) -C libft/ clean
	$(call logo)

fclean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJC)
	@$(MAKE) -C libft/ fclean
	@rm -rf $(SERVER)
	@rm -rf $(CLIENT)
	$(call logo)

re: fclean all

.PHONY: re all clean fclean
