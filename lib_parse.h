/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/28 15:15:39 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# include "libft/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

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
	char **export;	//varibale d'en exporter
	char **local_env; // varibale d'env locale + exporter
	char *oldpwd;
	char *pwd;
}						t_env;


typedef enum e_token_type
{
	TOKEN_WORD,            // 0 - Arguments, commandes, fichiers
	TOKEN_PIPE,            // 1 - |
	TOKEN_REDIRECT_IN,     // 2 - <
	TOKEN_REDIRECT_OUT,    // 3 - >
	TOKEN_REDIRECT_APPEND, // 4 - >>
	TOKEN_HEREDOC,         // 5 - <<
	TOKEN_EOF,             // 6 - EOF
	TOKEN_HERESTRING	   // 7 - <<<
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
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef struct s_ju_command
{
	char			**argv;
	t_redirect		*redirection;
	struct s_token	*next;
	struct s_token	*prev;
}						t_ju_command;

typedef struct t_commands
{
	char **argv;
	struct t_commands	*next;
	struct t_infiles *infiles;
	struct t_outfiles *outfiles;
}						t_commands;

typedef struct t_infiles
{
	char				*infile;
	int					fd;
	t_file_type			type;
	char				*word_eof;
	struct t_infiles	*next;
}						t_infiles;

typedef struct t_outfiles
{
	char				*outfile;
	int					fd;
	t_file_type			type;
	struct t_outfiles	*next;
}						t_outfiles;

// parse_input.c
t_commands	*manage_input(char *str, t_exitcode *exit_code); // gere l'input, //convertis en infos puis en **argv et en liste chainees
void		replace_azt(t_input_info *info, int i);

// check_input.c
void	is_complete(t_input_info *infos); // gere l'input et redirige en cas d'input incomplet + quote les backslash (note: rajouter une maniere de gerer l'historique de readline car la elle prend les deformations des backslash)
void	recall_readline(t_input_info *infos); // rappele la fonction readline de maniere propre pour certeine condition
int		next_simple_quote(t_input_info *infos, int i); // renvoi i = prochain " comme str[i] = '"'
void	quote_next_char(t_input_info *infos, int i); // quote str[i+ 1] proprement, ne renvoi pas i il faut penser a rajouter a 2 a sa valeur
int		next_double_quote(t_input_info *infos, int i, int init); // renvoi i = prochain ' comme str[i] = '\''

// expand_parse.c
void	replace_var_input(t_input_info *infos, t_exitcode *exit_code); // pour ;'instant ne gere que les variables en dehors de quotes
void	expand_var(t_input_info *infos, int i, int quote, t_exitcode *exit_code); // expans les variables d'environnement et retourne info->input malloc avec la variable d'environnement si elle existe
void	resize_and_copy(t_input_info *infos, int i, int j, char *temp_input);

// test
void	add_space_before(t_input_info *infos, int i);
void	define_operator(t_input_info *infos);
int		expand_in_quote(t_input_info *infos, int i, t_exitcode *exit_code);

//tokenization.c
t_token	*ft_lstnew_token(t_token_type type, char *content);
void	ft_lstadd_token_back(t_token **lst, t_token *new);
int	ft_get_op_length(char *input, int i, t_token_type *type);
char *ft_get_word(char *input, int start);
t_token	*ft_token(char *input);

//built_in.c
char		**ft_env(char **environ, t_env *env);	//init la struct env
int			env_built_in(t_env *env); //a besoin du char **environt qui est pris par le main apres argc et argv;
void		up_shell_level(char **env); //augmente le niveau du shell dans les variable d'env
void	ft_exit(t_env *env, int nbr_return);
void	free_env(t_env *env);

//parsing.c
int	count_words(t_token *token);
t_commands	*ft_lstnew_command(int words);
void	ft_lstadd_cmd_back(t_commands **lst, t_commands *new);
t_commands	*ft_init_cmd(t_token *token);

//parse_quotes_in_cmds.c
void	ft_check_quotes_struct_cmd(t_commands *commands);
char	*ft_check_quotes_argv(char *cmds, int len, int i, int j);

//parse_check_next_token.c
void	ft_check_next_token_heredoc(t_token *token);
void	ft_check_next_token_pipe(t_token *token);
void	ft_check_next_token_redir_in(t_token *token);
void	ft_check_next_token_redir_out(t_token *token);
void	ft_check_next_token_redir_append(t_token *token);
void	ft_check_next_token_herestring(t_token *token);
//void	recall_readline(t_token *infos);

// free_errors.c
// void	exit_with_message_and_free(char *str, t_token *token, int n);
void    ft_free_tokens(t_token *tokens);

//main.c
void	prompt_loop(t_env *env_s);

// a retirer
void print_tokens(t_token *tokens); //test pour voir la tokenisation


char	*clean_simple_quote(char *str); // faut rajouter le cas <<''>>
void	clean_quote_in_argv(char **argv);
char	*clean_double_quote(char *str); // faut rajouter le cas <<"">>

// init_redir.c
t_infiles	*ft_lstnew_redirect_in(char *filename, t_file_type type, char *word);
t_outfiles	*ft_lstnew_redirect_out(char *filename, t_file_type type);
void	ft_lstadd_infiles_back(t_infiles **lst, t_infiles *new);
void	ft_lstadd_outfiles_back(t_outfiles **lst, t_outfiles *new);
t_token	*ft_add_redir(t_token *token, t_commands *node);

void	print_redirections(t_commands *cmds);
//retirer le print


#endif
