
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_print_address.c ft_print_char.c ft_print_int.c ft_print_str.c \
ft_print_un_int.c ft_print_x.c ft_putnbr_base.c ft_printf.c \
ft_itoa.c ft_putstr_fd.c ft_strchr.c ft_strlen.c ft_strchr.c
OBJ = $(SRC:.c=.o)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean	
	rm -f $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re