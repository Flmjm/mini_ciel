NAME = Mini_Ciel

LIBS = -lreadline

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS =  src/main.c src/tokenization.c src/parsing.c \
      #src/parse_input.c \
      src/check_input.c \
      src/put_input_to_array.c \
      src/expand_parse.c \
      src/list_manage.c# 
		
OBJS = $(SRCS:.c=.o)

LIBFT_NAME = libft.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

# Couleurs
BLACK           = "\033[30m"
RED             = "\033[31m"
GREEN           = "\033[32m"
YELLOW          = "\033[33m"
BLUE            = "\033[34m"
PURPLE          = "\033[35m"
CYAN            = "\033[36m"
WHITE           = "\033[37m"
RESET           = "\033[0m"

RM = rm -rf

all: ${NAME}

$(LIBFT): $(LIBFT_DIR)
	make -C $(LIBFT_DIR) $(LIBFT_NAME)

${NAME}: ${OBJS} ${LIBFT}
		${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LIBS} -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@${MAKE} -C ./libft fclean
		@${RM} ${OBJS}

fclean: clean
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re