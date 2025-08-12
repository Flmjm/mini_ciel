NAME			= Mini_Ciel
LIBFT_NAME		= libft.a

CC 				= gcc
FLAGS 			= -Wall -Wextra -Werror -g

SRC 			= src/main.c
LIBFT			= libft/ft_bzero.c\
				  libft/ft_isalnum.c\
				  libft/ft_isalpha.c\
				  libft/ft_isascii.c\
				  libft/ft_isdigit.c\
				  libft/ft_isprint.c\
				  libft/ft_memcpy.c\
				  libft/ft_memset.c\
				  libft/ft_strlcpy.c\
				  libft/ft_strlcat.c\
				  libft/ft_strlen.c\
				  libft/ft_memmove.c\
				  libft/ft_toupper.c\
				  libft/ft_tolower.c\
				  libft/ft_strchr.c\
				  libft/ft_strrchr.c\
				  libft/ft_strncmp.c\
				  libft/ft_memchr.c\
				  libft/ft_memcmp.c\
				  libft/ft_strnstr.c\
				  libft/ft_atoi.c\
				  libft/ft_strdup.c\
				  libft/ft_calloc.c\
				  libft/ft_substr.c\
				  libft/ft_strjoin.c\
				  libft/ft_split.c\
				  libft/ft_itoa.c\
				  libft/ft_strtrim.c\
				  libft/ft_putchar_fd.c\
				  libft/ft_putstr_fd.c\
				  libft/ft_putendl_fd.c\
				  libft/ft_putnbr_fd.c\
				  libft/ft_strmapi.c\
				  libft/ft_striteri.c\
				  libft/ft_printf/ft_printf.c\
				  libft/ft_printf/printf_putnbr_base.c\
				  libft/ft_printf/printf_putstr.c\
				  libft/ft_printf/printf_putnbr_x.c\
				  libft/gnl/get_next_line.c

OBJ 			= $(SRC:.c=.o)
OBJ_LIBFT		= $(LIBFT:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

# La librairie doit être compilée avant le binaire
$(LIBFT_NAME): $(OBJ_LIBFT)
	@ar rcs $@ $^

# Le binaire dépend de ses objets ET de la librairie
$(NAME): $(OBJ) $(LIBFT_NAME)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) -lreadline

all: $(NAME)

test: all
	@echo "Compilation test terminée."

clean:
	@rm -f $(OBJ) $(OBJ_LIBFT)

fclean: clean
	@rm -f $(NAME) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re test
