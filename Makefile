NAME = minishell

LIBS = -lreadline -lhistory

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -O0 -no-pie -g

SRCS =  src/built_ins/built_in.c src/built_ins/cd_utils.c src/built_ins/cd.c src/built_ins/echo.c src/built_ins/exit.c src/built_ins/export.c \
		src/built_ins/pwd.c src/built_ins/unset.c src/exec/cmd_process.c src/exec/exec_builtin.c src/exec/exec_main.c src/exec/exit_code_and_signals.c \
		src/exec/free_errors_bonus.c src/exec/utils_files.c src/exec/utils_files2.c src/exec/utils.c src/parsing/check_input_utils.c \
		src/parsing/check_input.c src/parsing/check_next_token.c src/parsing/check_next_token2.c src/parsing/expand_parse.c src/parsing/expand_utils.c \
		src/parsing/init_redir.c src/parsing/parse_cmds.c src/parsing/parse_input.c src/parsing/parse_quotes_in_cmds.c src/parsing/tokenization_utils.c \
		src/parsing/tokenization.c main.c src/built_ins/export_utils.c src/built_ins/env_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_NAME = libft.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

RM = rm -rf

all: ${NAME}

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) $(LIBFT_NAME)

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LIBS} -o ${NAME}

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@${MAKE} -C ./libft fclean
	@${RM} ${OBJS}


test: ${OBJS} ${LIBFT}
	@${CC} -g ${OBJS} ${LIBFT} ${LIBS} -o ${NAME}


fclean: clean
	@${RM} ${NAME} $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re
