NAME = server
NAMEC = client
SRCS = Server_bonus.c
OBJS = $(SRCS:.c=.o)
SRCC = Client_bonus.c
OBJC = $(SRCC:.c=.o)
CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LIBPFP = ./ft_printf/
LIBPF = $(LIBPFP)libftprintf.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:  $(NAME) $(NAMEC) $(LIBPF)

$(NAME): $(OBJS) $(LIBPF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBPF) -o $(NAME)

$(NAMEC): $(OBJC) $(LIBPF)
	$(CC) $(CFLAGS) $(OBJC) $(LIBPF) -o $(NAMEC)

$(LIBPF):
	@make -C $(LIBPFP)

clean:
	$(RM) $(OBJS) $(OBJSC)
	@make clean -C $(LIBPFP)

fclean: clean
	$(RM) $(NAME) $(NAMEC)
	@make fclean -C $(LIBPFP) 

re: fclean all

.PHONY: all flean clean re
