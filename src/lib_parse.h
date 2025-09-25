/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/25 11:39:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# include "../libft/libft.h"
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

typedef	struct s_env
{
	char **export;	//varibale d'en exporter
	char **local_env; // varibale d'env locale + exporter
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
	t_token_type	type;
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

typedef struct t_arguments
{
	char				*arg;
	struct t_arguments	*next;
}						t_arguments;

typedef struct t_infiles
{
	char				*infile;
	struct t_infiles	*next;
}						t_infiles;

typedef struct t_outfiles
{
	char				*outfile;
	struct t_outfiles	*next;
}						t_outfiles;

// parse_input.c
void	manage_input(char *str); // gere l'input, //convertis en infos puis en **argv et en liste chainees
void	erase_in_str(t_input_info *infos, int i); // suprime proprement infos->input[i] dans sa chaine
int		how_much_args(t_input_info *infos); // retourne le nombre d'arguments passer a readline
int		next_space(char *str, int i); // useless
void	replace_backslash_double_quote(t_input_info *infos); // useless

// put_input_to_array.c
int		strlen_of_args(t_input_info *infos, int start); // start = numeros de l'argument dans infos, retourne sa taille complete
char	**convert_input_to_array(t_input_info *infos); // recupere l'input clean et le convertis en **argv
void	copy_arg(t_input_info *infos, char *buffer, int arg); // copie l'argument numeros arg de infos->input a buffer

// list_manage.c
int		is_redirection(char *str); // check et renvoie selon si l'argument est une direction (a changer)
int		check_operator_in_str(const char *str); // pareil a changer

// check_input.c
void	is_complete(t_input_info *infos); // gere l'input et redirige en cas d'input incomplet + quote les backslash (note: rajouter une maniere de gerer l'historique de readline car la elle prend les deformations des backslash)
void	recall_readline(t_input_info *infos); // rappele la fonction readline de maniere propre pour certeine condition
int		next_simple_quote(t_input_info *infos, int i); // renvoi i = prochain " comme str[i] = '"'
void	quote_next_char(t_input_info *infos, int i); // quote str[i+ 1] proprement, ne renvoi pas i il faut penser a rajouter a 2 a sa valeur
int		next_double_quote(t_input_info *infos, int i, int init); // renvoi i = prochain ' comme str[i] = '\''

// expand_parse.c
void	replace_var_input(t_input_info *infos); // pour ;'instant ne gere que les variables en dehors de quotes
void	expand_var(t_input_info *infos, int i, int quote); // expans les variables d'environnement et retourne info->input malloc avec la variable d'environnement si elle existe
void	resize_and_copy(t_input_info *infos, int i, int j, char *temp_input);

// test
void	add_space_before(t_input_info *infos, int i);
void	define_operator(t_input_info *infos);
int		expand_in_quote(t_input_info *infos, int i);

//tokenization.c
t_token	*ft_lstnew_token(t_token_type type, char *content);
void	ft_lstadd_token_back(t_token **lst, t_token *new);
int	ft_get_op_length(char *input, int i, t_token_type *type);
char *ft_get_word(char *input, int start);
t_token	*ft_token(char *input);

//built_in.c
char		**ft_env(char **environ);	//init la struct env
int			env(t_env *env); //a besoin du char **environt qui est pris par le main apres argc et argv;
void		up_shell_level(char **env); //augmente le niveau du shell dans les variable d'env
void	ft_exit(t_env *env);
void	free_env(t_env *env);

//parsing.c
void	ft_check_next_token(t_token *token);
void	ft_init_file(t_token *token);
t_redirect	*ft_lstnew_redirect(char *filename);
void	ft_lstadd_redirect_back(t_redirect **lst, t_redirect *new);

//parse_check_next_token.c
void	ft_check_next_token_heredoc(t_token *token);
void	ft_check_next_token_pipe(t_token *token);
void	ft_check_next_token_redir_in(t_token *token);
void	ft_check_next_token_redir_out(t_token *token);
void	ft_check_next_token_redir_append(t_token *token);
void	ft_check_next_token_herestring(t_token *token);
//void	recall_readline(t_token *infos);

// free_errors.c
void	exit_with_message_and_free(char *str, t_token *token, int n);
void    ft_free_tokens(t_token *tokens);

//main.c
void prompt_loop(char *input, t_env *env_s);

// a retirer
void print_tokens(t_token *tokens); //test pour voir la tokenisation



t_commands	*sep_cmd(t_token *input);
void	add_node_cmds(t_commands **commands, t_commands	*new);
int		how_many_args(t_token	*input);
void print_cmds(t_commands *cmds);
void	print_test(t_commands **test);

#endif
