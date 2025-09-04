NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF_SRC = ft_printf/ft_printf.c \
	ft_printf/printf_putnbr_base.c \
	ft_printf/printf_putstr.c \
	ft_printf/printf_putnbr_x.c

GNL_SRC = gnl/get_next_line.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
PRINTF_OBJ = $(PRINTF_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)

ALL_OBJ = $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
	ar rcs $(NAME) $^

bonus: $(ALL_OBJ)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

