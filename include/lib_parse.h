/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/15 22:27:33 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

#define _POSIX_C_SOURCE 200809L

# include "../libft/libft.h"
# include "colors.h"
# include <signal.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

# ifndef PROMPT_LINE
#  define PROMPT_LINE BBLUE ".~Mini_ciel~> " BWHITE
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

typedef struct s_exitcode
{
	int last_cmd;
}	t_exitcode;

typedef	struct s_env
{
	char **global;
	struct s_env_local *local;
	char *oldpwd;
	char *pwd;
	struct sigaction *signal;

}						t_env;

typedef struct s_env_local
{
	char *value;
	struct s_env_local *next;
}						t_env_local;

typedef enum e_token_type
{
	TOKEN_WORD,            // 0 - Arguments, commandes, fichiers
	TOKEN_PIPE,            // 1 - |
	TOKEN_REDIRECT_IN,     // 2 - <
	TOKEN_REDIRECT_OUT,    // 3 - >
	TOKEN_REDIRECT_APPEND, // 4 - >>
	TOKEN_HEREDOC,         // 5 - <<
	TOKEN_EOF,             // 6 - EOF
	TOKEN_HERESTRING,	   // 7 - <<<
	TOKEN_VAR			   // 8 - cmd=aled
	}						t_token_type;

typedef enum e_file_type
{
	FILE_REDIRECT_IN = 2,		// <
	FILE_REDIRECT_OUT = 3,    	// >
	FILE_REDIRECT_APPEND = 4, 	// >>
	FILE_HEREDOC = 5, 			// <<
}							t_file_type;

typedef struct t_input_info
{
	int					nbr_args;
	char				**argv;
	char				*input;
}						t_input_info;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}						t_token;


typedef struct s_redirect
{
	t_file_type		type;
	char			*filename;
	int				fd;
	char				*word_eof;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef struct t_commands
{
	char **argv;
	struct t_commands	*next;
	struct t_redirect	*redirect;
}						t_commands;


// main.c
void 	manage_ctrlc(int sig);
void	prompt_loop(t_env *env_s);
char	*prompt_sentence(t_env *env);

/// PARSING ///

// check_input.c
void	is_complete(t_input_info *infos); // gere l'input et redirige en cas d'input incomplet + quote les backslash (note: rajouter une maniere de gerer l'historique de readline car la elle prend les deformations des backslash)
void	recall_readline(t_input_info *infos); // rappele la fonction readline de maniere propre pour certeine condition
int	next_simple_quote(t_input_info *infos, int i, int init); // renvoi i = prochain " comme str[i] = '"'
void	quote_next_char(t_input_info *infos, int i); // quote str[i+ 1] proprement, ne renvoi pas i il faut penser a rajouter a 2 a sa valeur
int		next_double_quote(t_input_info *infos, int i, int init); // renvoi i = prochain ' comme str[i] = '\''
void		replace_azt(t_input_info *info, int i);;

//check_next_token.c
int	ft_check_next_token_heredoc(t_token *token);
int	ft_check_next_token_herestring(t_token *token);
int	ft_check_next_token_pipe(t_token *token);
int	ft_check_next_token_redir_in(t_token *token);
int	ft_check_next_token_redir_out(t_token *token);

//check_next_token2.c
int	ft_check_next_token_redir_append(t_token *token);
int	ft_check_next_token(t_token *token);

// expand_parse.c
void	replace_var_input(t_input_info *infos, t_exitcode *exit_code); // pour ;'instant ne gere que les variables en dehors de quotes
int	expand_in_quote(t_input_info *infos, int i, t_exitcode *exit_code);
int	extract_var_name(char *input, int i, int quote, char *env_input);
void	expand_var(t_input_info *infos, int i, int quote, t_exitcode *exit_code); // expans les variables d'environnement et retourne info->input malloc avec la variable d'environnement si elle existe

// expand_utils.c
void	erase_in_str(t_input_info *infos, int i);
void resize_and_copy(t_input_info *infos, int i, int j, char *temp_input);


// init_redir.c
t_redirect	*ft_lstnew_redirect(char *filename, t_file_type type, char *word);
void	ft_lstadd_redirect_back(t_redirect **lst, t_redirect *new);
void	ft_add_single_redir(t_token *token, t_commands *node);
t_token	*ft_add_redir(t_token *token, t_commands *node);

//parse_cmds.c
int	count_words(t_token *token);
t_commands	*ft_lstnew_command(int words);
void	ft_lstadd_cmd_back(t_commands **lst, t_commands *new);
t_commands	*ft_init_cmd(t_token *token);

// parse_input.c
t_commands	*manage_input(char *str, t_exitcode *exit_code); // gere l'input, //convertis en infos puis en **argv et en liste chainees

//parse_quotes_in_cmds.c
void	ft_check_quotes_struct_cmd(t_commands *commands);
char	*ft_check_quotes_argv(char *cmds, int len, int i, int j);

//tokenization_utils.c
t_token	*ft_lstnew_token(t_token_type type, char *content);
void	ft_lstadd_token_back(t_token **lst, t_token *new);
int	ft_is_separator(char c);
int get_op_redir_in(char *input, int i, t_token_type *type);
int	ft_get_op_length(char *input, int i, t_token_type *type);

//tokenization.c
int	ft_process_quotes(char *input, int i, int *in_quotes, char *quote);
char	*ft_get_word(char *input, int start);
int	ft_handle_operator(char *input, int i, t_token **token);
int	ft_handle_word(char *input, int i, t_token **token);
t_token	*ft_token(char *input, int i);

// export.c
int	ft_strlen_var(const char *str);

#endif
