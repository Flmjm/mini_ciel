/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:45:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/11 15:28:46 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	replace_var_input(t_input_info *infos, t_exitcode *exit_code)
{
	int	i;

	i = 0;
	while (infos->input[i])
	{
		while (infos->input[i] && infos->input[i] == ' ')
			i++;
		if (infos->input[i] == '"')
			i = expand_in_quote(infos, i, exit_code);
		else if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i, FALSE);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_'
				|| infos->input[i + 1] == '?'))
			expand_var(infos, i, 0, exit_code);
		else if (infos->input[i])
			i++;
		if (i >= ft_strlen(infos->input))
			break ;
	}
}

int	expand_in_quote(t_input_info *infos, int i, t_exitcode *exit_code)
{
	i++;
	while (infos->input[i] && infos->input[i] != '"')
	{
		if (infos->input[i] == '\'' && infos->input[i + 1]
			&& infos->input[i + 2] == '\'')
			i += 3;
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '$')
			erase_in_str(infos, i);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_'
				|| infos->input[i + 1] == '?'))
			expand_var(infos, i, 1, exit_code);
		else
			i++;
	}
	return (i);
}

int	extract_var_name(char *input, int i, int quote, char *env_input)
{
	int	j;

	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		if (quote && input[i] == '"')
			break ;
		env_input[j++] = input[i++];
	}
	env_input[j] = '\0';
	return (j);
}

void	expand_var(t_input_info *infos, int i, int quote, t_exitcode *exit_code)
{
	char	*temp_input;
	char	env_input[20];
	int		var_len;

	i++;
	if (infos->input[i] == '?')
	{
		env_input[0] = '?';
		env_input[1] = '\0';
		temp_input = ft_itoa(exit_code->last_cmd);
		resize_and_copy(infos, i, 1, temp_input);
		return ;
	}
	if (!ft_isalnum(infos->input[i]) && infos->input[i] != '_')
		return ;
	var_len = extract_var_name(infos->input, i, quote, env_input);
	temp_input = getenv(env_input);
	if (!temp_input)
		return ;
	resize_and_copy(infos, i + var_len, var_len, temp_input);
}
