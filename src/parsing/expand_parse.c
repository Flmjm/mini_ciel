/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:45:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/03 16:36:13 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	replace_var_input(t_input_info *infos, t_env *env)
{
	int	i;

	i = 0;
	while (infos->input[i])
	{
		while (infos->input[i] && infos->input[i] == ' ')
			i++;
		if (infos->input[i] == '"')
			i = expand_in_quote(infos, i, env);
		else if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i, FALSE);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_'
				|| infos->input[i + 1] == '?'))
		{
			expand_var(infos, i, 0, env);
			i = 0;
		}
		else if (infos->input[i] == '$' && infos->input[i + 1])
			i++;
		else if (infos->input[i])
			i++;
		if (i >= ft_strlen(infos->input))
			break ;
	}
}

int	expand_in_quote(t_input_info *infos, int i, t_env *env)
{
	i++;
	while (infos->input[i] && infos->input[i] != '"')
	{
		if (infos->input[i] == '\'' && infos->input[i + 1] && infos->input[i
				+ 2] == '\'')
			i += 2;
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '$')
			erase_in_str(infos, i);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_'
				|| infos->input[i + 1] == '?'))
		{
			expand_var(infos, i, 1, env);
			i = 0;
		}
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

void	expand_var(t_input_info *infos, int i, int quote, t_env *env)
{
	char	*temp_input;
	char	env_input[MAX_INPUT];
	int		var_len;

	i++;
	if (ft_strncmp(infos->input + i, "EMPTY", 5) == 0)
	{
		expand_empty(infos, i, NULL);
		return ;
	}
	if (infos->input[i] == '?')
	{
		env_input[0] = '?';
		env_input[1] = '\0';
		temp_input = ft_itoa(env->exitcode->last_cmd);
		resize_and_copy(infos, i + 1, 1, temp_input);
		return ;
	}
	if (!ft_isalnum(infos->input[i]) && infos->input[i] != '_')
		return ;
	var_len = extract_var_name(infos->input, i, quote, env_input);
	temp_input = get_env_by_name(env_input, env);
	resize_and_copy(infos, i + var_len, var_len, temp_input);
}

void	expand_empty(t_input_info *infos, int i, char *temp_input)
{
	if (!infos->input[i + 5] && i - 1 < 0)
	{
		infos->input = NULL;
		return ;
	}
	resize_and_copy(infos, i + 5, 5, temp_input);
}
