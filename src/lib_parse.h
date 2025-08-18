/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/16 06:07:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# ifndef PROMPT_LINE
# define PROMPT_LINE ".test> "
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
	char	**input;
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


# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

// parse_input.c
void *manage_input(char *str); //convertis l'input de readline en infos puis en **argv et en liste chainees
void	init_info(t_input_info *infos, char *str);
void	is_complete(char *str);
int	find_end_operator(char *str, char end, char end2, int i);
void	recall_readline(char *str);



// list_manage.c
int     		is_redirection(char *str);
int				check_operator_in_str(const char *str);

# endif
