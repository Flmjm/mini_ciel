/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/27 18:54:54 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

t_commands	*manage_input(char *str, t_env *env)
{
	t_input_info	*infos;
	t_token			*token;
	t_commands		*cmds;

	infos = ft_malloc(sizeof(t_input_info), 0);
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	replace_var_input(infos, env);
	token = ft_token(infos->input, 0);
	if (!token)
		return (NULL);
	cmds = ft_init_cmd(token);
	clean_var(cmds);
	if (cmds)
		ft_check_quotes_struct_cmd(cmds);
	return (cmds);
}
