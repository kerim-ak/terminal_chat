NAME = minitalk
SERVER = server
CLIENT = client
FT_PRINTF = ft_printf/libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): server.c minitalk.h
	make -C ft_printf
	$(CC) $(CFLAGS) server.c $(FT_PRINTF) -o server

$(CLIENT): client.c minitalk.h
	make -C ft_printf
	$(CC) $(CFLAGS) client.c $(FT_PRINTF) -o client

clean:
	make -C ft_printf clean

fclean: clean
	make -C ft_printf fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all $(NAME) clean fclean re

 