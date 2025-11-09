/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/09 21:23:53 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

t_commands *manage_input(char *str, t_exitcode *exit_code) //verifie l'input de readline et la passe en **argv et en liste chainees
{
	t_input_info *infos;
	t_token *token;
	t_commands	*cmds;

	infos = ft_malloc(sizeof(t_input_info), 0);
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	replace_var_input(infos, exit_code);
	token = ft_token(infos->input);
	if (!token)
		return;
	print_tokens(token);
	cmds = ft_init_cmd(token);
	if (cmds)
		ft_check_quotes_struct_cmd(cmds);
	print_redirections(cmds);
	return (cmds);
}

void print_tokens(t_token *tokens) {
    printf("\n=== TOKENS ===\n");
    t_token *current = tokens;
    int index = 0;

    while (current) {
        printf("[%d] %d: '%s'\n",
               index,
               current->type,
               current->value);
        current = current->next;
		index++;
    }
    printf("\n");
}


void	print_redirections(t_commands *cmds)
{
int			i;
t_infiles	*in;
t_outfiles	*out;
int			cmd_index;
cmd_index = 1;
while (cmds)
{
	printf("=== Commande %d ===\n", cmd_index);
	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		printf("  argv[%d]: %s\n", i, cmds->argv[i]);
		i++;
	}
	in = cmds->infiles;
	out = cmds->outfiles;
	if (!in && !out)
		printf("  (Aucune redirection)\n");
	if (in)
	{
		printf("  Infiles:\n");
		while (in)
		{
			if (in->type == FILE_HEREDOC)
				printf("    - %s (type: << // EOF: %s)\n", in->infile, in->word_eof);
			else if (in->type == FILE_REDIRECT_IN)
				printf("    - %s (type: < // EOF: %s)\n", in->infile, in->word_eof);
			in = in->next;
		}
	}
	if (out)
	{
		printf("  Outfiles:\n");
		while (out)
		{
			if (out->type == FILE_REDIRECT_APPEND)
				printf("    - %s (type: >>)\n", out->outfile);
			else if (out->type == FILE_REDIRECT_OUT)
				printf("    - %s (type: >)\n", out->outfile);
			out = out->next;
		}
	}
	printf("\n");
	cmds = cmds->next;
	cmd_index++;
}
}
