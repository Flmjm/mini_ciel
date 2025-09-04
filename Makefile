NAME            = Mini_Ciel

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror -g

SRC = src/main.c \
      src/tokenization.c
      #src/parse_input.c \
      src/check_input.c \
      src/put_input_to_array.c \
      src/expand_parse.c \
      src/list_manage.c# \

OBJ             = $(SRC:.c=.o)

LIBFT_NAME = libft.a
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/$(LIBFT_NAME)

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

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Compilation de libft
$(LIBFT):
	@echo "Compilation de libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Règle principale
$(NAME): $(OBJ) $(LIBFT)
	@echo "Liaison des objets avec libft..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo $(GREEN)"Compilation terminée : $(NAME)"$(RESET)

all: $(NAME)

test: $(OBJ) $(LIBFT)
	@echo "Compilation test..."
	clang $(CFLAGS) -I$(LIBFT_DIR) $(SRC) $(LIBFT) -o $(NAME) -lreadline
	@echo $(PURPLE)"Compilation test terminée."$(RESET)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW)"Fichiers objets supprimés."$(RESET)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(RED)"Nettoyage complet."$(RESET)

re: fclean all

.PHONY: all clean fclean re test