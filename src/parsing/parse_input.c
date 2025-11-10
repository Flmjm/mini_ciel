/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/10 14:33:08 by juliette-ma      ###   ########.fr       */
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
	token = ft_token(infos->input, 0);
	if (!token)
		return (NULL);
	//print_tokens(token);
	cmds = ft_init_cmd(token);
	if (cmds)
		ft_check_quotes_struct_cmd(cmds);
	//print_redirections(cmds);
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


// void	print_redirections(t_commands *cmds)
// {
// int			i;
// t_redirect	*redir;
// int			cmd_index;
// cmd_index = 1;
// while (cmds)
// {
// 	printf("=== Commande %d ===\n", cmd_index);
// 	i = 0;
// 	while (cmds->argv && cmds->argv[i])
// 	{
// 		printf("  argv[%d]: %s\n", i, cmds->argv[i]);
// 		i++;
// 	}
// 	redir = cmds->redirect;
// 	if (!redir)
// 		printf("  (Aucune redirection)\n");
// 	if (redir)
// 	{
// 		printf("  Files:\n");
// 		while (redir)
// 		{
// 			if (redir->type == FILE_HEREDOC)
// 				printf("    - %s (type: << // EOF: %s)\n", redir->filename, redir->word_eof);
// 			else if (redir->type == FILE_REDIRECT_IN)
// 				printf("    - %s (type: < // EOF: %s)\n", redir->filename, redir->word_eof);
// 			else if (redir->type == FILE_REDIRECT_APPEND)
// 				printf("    - %s (type: >>)\n", redir->filename);
// 			else if (redir->type == FILE_REDIRECT_OUT)
// 				printf("    - %s (type: >)\n", redir->filename);
// 			redir = redir->next;
// 		}
// 	}
// 	printf("\n");
// 	cmds = cmds->next;
// 	cmd_index++;
// }
// }
