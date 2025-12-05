/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/05 18:29:24 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# define _POSIX_C_SOURCE 200809L

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# include "../libft/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

// # ifndef PROMPT_LINE
// #  define PROMPT_LINE BBLUE ".~Mini_ciel~> " BWHITE
// # endif

typedef struct s_exitcode
{
	int					last_cmd;
	int					here_doc_error;
}						t_exitcode;

typedef struct s_env
{
	char				**global;
	struct s_exitcode	*exitcode;
	char				*oldpwd;
	char				*pwd;
	struct sigaction	*signal;
}						t_env;

typedef enum e_token_type
{
	TOKEN_WORD,				// 0 - Arguments, commandes, fichiers
	TOKEN_PIPE,				// 1 - |
	TOKEN_REDIRECT_IN,		// 2 - <
	TOKEN_REDIRECT_OUT,		// 3 - >
	TOKEN_REDIRECT_APPEND,	// 4 - >>
	TOKEN_HEREDOC,			// 5 - <<
	TOKEN_EOF,				// 6 - EOF
	TOKEN_HERESTRING,		// 7 - <<<
}						t_token_type;

typedef enum e_file_type
{
	FILE_REDIRECT_IN = 2,		// <
	FILE_REDIRECT_OUT = 3,		// >
	FILE_REDIRECT_APPEND = 4,	// >>
	FILE_HEREDOC = 5,			// <<
}						t_file_type;

typedef struct t_input_info
{
	int					nbr_args;
	char				**argv;
	char				*input;
}						t_input_info;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct t_redirect
{
	t_file_type			type;
	char				*filename;
	int					fd;
	char				*word_eof;
	struct t_redirect	*next;
	struct t_redirect	*prev;
}						t_redirect;

typedef struct t_commands
{
	char				**argv;
	struct t_commands	*next;
	struct t_redirect	*redirect;
}						t_commands;

// main.c
void					manage_ctrlc(int sig);
void					prompt_loop(t_env *env_s);
char					*prompt_sentence(t_env *env);

/// PARSING ///

// check_input.c
void					is_complete(t_input_info *infos);
void					recall_readline(t_input_info *infos);
int						next_simple_quote(t_input_info *infos, int i, int init);
void					quote_next_char(t_input_info *infos, int i);
int						next_double_quote(t_input_info *infos, int i, int init);
void					replace_azt(t_input_info *info, int i);

// check_next_token.c
int						ft_check_next_token_heredoc(t_token *token);
int						ft_check_next_token_herestring(t_token *token);
int						ft_check_next_token_pipe(t_token *token);
int						ft_check_next_token_redir_in(t_token *token);
int						ft_check_next_token_redir_out(t_token *token);

// check_next_token2.c
int						ft_check_next_token_redir_append(t_token *token);
int						ft_check_next_token(t_token *token);

// expand_parse.c
void					replace_var_input(t_input_info *infos,
							t_env *env);
int						expand_in_quote(t_input_info *infos, int i, t_env *env);
int						extract_var_name(char *input, int i, int quote,
							char *env_input);
void					expand_var(t_input_info *infos, int i, int quote,
							t_env *env);
void					expand_empty(t_input_info *infos, int i,
							char *temp_input);

// expand_utils.c
void					erase_in_str(t_input_info *infos, int i);
void					resize_and_copy(t_input_info *infos, int i, int j,
							char *temp_input);

// init_redir.c
struct t_redirect		*ft_lstnew_redirect(char *filename, t_file_type type,
							char *word);
void					ft_lstadd_redirect_back(t_redirect **lst,
							t_redirect *new);
void					ft_add_single_redir(t_token *token, t_commands *node);
t_token					*ft_add_redir(t_token *token, t_commands *node);

// parse_cmds.c
int						count_words(t_token *token);
t_commands				*ft_lstnew_command(int words);
void					ft_lstadd_cmd_back(t_commands **lst, t_commands *new);
t_commands				*ft_init_cmd(t_token *token);

// parse_input.c
t_commands				*manage_input(char *str, t_env *env);

// parse_quotes_in_cmds.c
void					ft_check_quotes_struct_cmd(t_commands *commands);
char					*ft_check_quotes_argv(char *cmds, int len, int i,
							int j);
char					*get_env_by_name(char *var_temp, t_env *env);

// tokenization_utils.c
struct s_token			*ft_lstnew_token(t_token_type type, char *content);
void					ft_lstadd_token_back(t_token **lst, t_token *new);
int						ft_is_separator(char c);
int						get_op_redir_in(char *input, int i, t_token_type *type);
int						ft_get_op_length(char *input, int i,
							t_token_type *type);

// tokenization.c
int						ft_process_quotes(char *input, int i, int *in_quotes,
							char *quote);
char					*ft_get_word(char *input, int start);
int						ft_handle_operator(char *input, int i, t_token **token);
int						ft_handle_word(char *input, int i, t_token **token);
struct s_token			*ft_token(char *input, int i);

// export.c
int						ft_strlen_var(const char *str);

// check_input_utils.c
void					replace_and_recall(t_input_info *infos, int i);
void					clean_var(t_commands *cmds);
char					*get_var_value(int k, int j, int i, t_env *env);

// env_utils.c
int						ft_length_env(char **environ);
char					**add_basic_env(char **env_copy);

#endif
