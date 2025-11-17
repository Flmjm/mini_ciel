/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/17 01:11:38 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	is_var(t_token *token);

t_commands	*manage_input(char *str, t_exitcode *exit_code)
{
	t_input_info	*infos;
	t_token			*token;
	t_commands		*cmds;

	infos = ft_malloc(sizeof(t_input_info), 0);
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	replace_var_input(infos, exit_code);
	token = ft_token(infos->input, 0);
	is_var(token);
	if (!token)
		return (NULL);
	cmds = ft_init_cmd(token);
	if (cmds)
		ft_check_quotes_struct_cmd(cmds);
	return (cmds);
}

void	is_var(t_token *token)
{
	int		i;
	t_token	*current;

	current = token;
	i = 0;
	while (current)
	{
		if (token->type == 0 && ft_strlen(token->value) > 1)
		{
			while (token->value[i])
			{
				if (token->value[i] == '=')
				{
					token->type = TOKEN_VAR;
				}
				i++;
			}
		}
		current = current->next;
	}
}
