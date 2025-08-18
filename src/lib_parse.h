/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/19 00:20:42 by root             ###   ########.fr       */
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
	int		nbr_commands;
	int		nbr_arguments;
	int		nbr_operators;
	int		args;
	char	*input;
} t_input_info;

typedef struct t_commands
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
	struct t_infiles *next;
} t_infiles;

typedef struct t_outfiles
{
	char	*outfile;
	struct t_outfiles *next;
} t_outfiles;

// parse_input.c
void 			*manage_input(char *str); //gere l'input, convertis en infos puis en **argv et en liste chainees
void			is_complete(t_input_info *infos); // gere l'input et redirige en cas d'input incomplet
void			recall_readline(t_input_info *infos); // rappele la fonction readline de maniere propre pour certeine condition
int				next_simple_quote(t_input_info *infos, int i); //renvoi i = prochain " comme str[i] = '"'
void			quote_next_char(t_input_info *infos, int i); //quote str[i + 1] proprement, ne renvoi pas i il faut penser a rajouter a 2 a sa valeur
int				next_double_quote(t_input_info *infos, int i);//renvoi i = prochain ' comme str[i] = '\''

// list_manage.c
int     		is_redirection(char *str);
int				check_operator_in_str(const char *str);

# endif
