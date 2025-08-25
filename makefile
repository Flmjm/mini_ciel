NAME			= Mini_Ciel
LIBFT_NAME		= libft.a

CC 				= gcc
FLAGS 			= -Wall -Wextra -Werror -g

SRC 			= src/main.c \
				  src/parse_input.c \
				  src/check_input.c \
				  src/put_input_to_array.c

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

BLACK			=      "\033[30m"
RED         	=		"\033[31m"
GREEN       	=		"\033[32m"
YELLOW      	=		"\033[33m"
BLUE        	=		"\033[34m"
PURPLE      	=		"\033[35m"
CYAN       		=		"\033[36m"
WHITE       	=		"\033[37m"
RESET       	=		"\033[0m"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_NAME): $(OBJ_LIBFT)
	@ar rcs $@ $^

$(NAME): $(OBJ) $(LIBFT_NAME)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) -lreadline

all: $(NAME)

test: $(LIBFT_NAME)
	clang $(SRC) $(LIBFT_NAME) -o $(NAME) -lreadline
	@echo  $(PURPLE)"Compilation test terminée." $(RESET)

clean:
	@rm -f $(OBJ) $(OBJ_LIBFT)
	@echo $(YELLOW)"*.o delete "$(RESET)
fclean:
	@rm -f $(OBJ) $(OBJ_LIBFT) # clean
	@rm -f $(NAME) $(LIBFT_NAME)
	@echo $(RED)" ./ delete"$(RESET)

re:
	@rm -f $(OBJ) $(OBJ_LIBFT) # clean
	@rm -f $(NAME) $(LIBFT_NAME) #fclean
	@echo  $(BLUE)"Make re complete !" $(RESET)

.PHONY: all clean fclean re test
