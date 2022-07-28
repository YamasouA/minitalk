CC  =   gcc
CFLAGS   =   -Wall -Wextra -Werror
NAME    =   minitalk
SERVER  =   server
CLIENT  =   client
LIBFT   =   libft/libft.a
SERVER_SRCS	=   server.c 
CLIENT_SRCS	=   client.c
SERVER_OBJS    =   $(SERVER_SRCS:%.c=%.o)
CLIENT_OBJS    =   $(CLIENT_SRCS:%.c=%.o)

all:    $(NAME)

$(NAME): $(SERVER) $(CLIENT) $(OBJS)

$(SERVER):	$(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(LIBFT) $(SERVER_OBJS)
$(CLIENT):	$(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(LIBFT) $(CLIENT_OBJS)
$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(SERVER_OBJS)
	rm -f $(CLIENT_OBJS)
fclean: clean
	make fclean -C libft
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
