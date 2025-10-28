/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/28 14:50:02 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

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
	print_tokens(token);
	cmds = ft_init_cmd(token);
	ft_check_quotes_struct_cmd(cmds);
	print_redirections(cmds);
	return (cmds);

	//print_cmds(cmds);
	//free(token);
	//free(infos);
}
