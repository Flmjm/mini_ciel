/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/26 22:59:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "colors.h"

# ifndef PROMPT_LINE
# define PROMPT_LINE BBLUE".~Mini_ciel~> "BWHITE
# endif

# ifndef FALSE
# define FALSE 0
# endif

# ifndef TRUE
# define TRUE 1
# endif

typedef struct t_input_info
{
	int		nbr_args;
	char	**argv;
	char	*input;
} t_input_info;

typedef struct t_commands // prochain commit je fait en sorte d'init les listes chainee promis
{
	int nbr_commands;
	char *command;
	struct t_arguments	*arguments;
	struct t_infiles	*infiles;
	struct t_outfiles	*outfiles;
} t_commands;

typedef struct t_arguments
{
	char	*arg;
	struct t_arguments *next;
} t_arguments;

typedef struct t_infiles
{
	char	*infile;
	char	*type;
	struct t_infiles *next;
} t_infiles;

typedef struct t_outfiles
{
	char	*outfile;
	char	*type;
	struct t_outfiles *next;
} t_outfiles;

// parse_input.c
void 			*manage_input(char *str); //gere l'input, convertis en infos puis en **argv et en liste chainees
void			erase_in_str(t_input_info *infos, int i); //suprime proprement infos->input[i] dans sa chaine
int				how_much_args(t_input_info *infos); // retourne le nombre d'arguments passer a readline
int				next_space(char *str, int i); // useless
void			replace_backslash_double_quote(t_input_info *infos); // useless

// put_input_to_array.c
int				strlen_of_args(t_input_info *infos, int start); //start = numeros de l'argument dans infos, retourne sa taille complete
char			**convert_input_to_array(t_input_info *infos); //recupere l'input clean et le convertis en **argv
void			copy_arg(t_input_info *infos, char *buffer, int arg); //copie l'argument numeros arg de infos->input a buffer

// list_manage.c
int     		is_redirection(char *str); // check et renvoie selon si l'argument est une direction (a changer)
int				check_operator_in_str(const char *str); // pareil a changer 

// check_input.c
void			is_complete(t_input_info *infos); // gere l'input et redirige en cas d'input incomplet + quote les backslash (note: rajouter une maniere de gerer l'historique de readline car la elle prend les deformations des backslash)
void			recall_readline(t_input_info *infos); // rappele la fonction readline de maniere propre pour certeine condition
int				next_simple_quote(t_input_info *infos, int i); //renvoi i = prochain " comme str[i] = '"'
void			quote_next_char(t_input_info *infos, int i); //quote str[i + 1] proprement, ne renvoi pas i il faut penser a rajouter a 2 a sa valeur
int				next_double_quote(t_input_info *infos, int i, int init);//renvoi i = prochain ' comme str[i] = '\''

// expand_parse.c
void    		replace_var_input(t_input_info *infos); //pour ;'instant ne gere que les variables en dehors de quotes
void    		expand_var(t_input_info *infos, int i); //expans les variables d'environnement et retourne info->input malloc avec la variable d'environnement si elle existe

# endif
