/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:44:15 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/11 13:20:32 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

int	ft_process_quotes(char *input, int i, int *in_quotes, char *quote)
{
	if (*in_quotes == 0 && (input[i] == '"' || input[i] == '\''))
	{
		*in_quotes = 1;
		*quote = input[i];
	}
	else if (*in_quotes == 1)
	{
		if (input[i] == '\'' && input[i + 1] && input[i + 2] == '\''
			&& *quote == '"')
			return (i + 2);
		else if (input[i] == *quote)
			*in_quotes = 0;
	}
	return (i);
}

char	*ft_get_word(char *input, int start)
{
	int		i;
	int		in_quotes;
	char	quote;

	i = start;
	in_quotes = 0;
	while (input[i])
	{
		if (in_quotes == 0 && ft_is_separator(input[i]))
			break ;
		i = ft_process_quotes(input, i, &in_quotes, &quote);
		i++;
	}
	if (i > start)
		return (ft_substr(input, start, i - start));
	return (NULL);
}

int	ft_handle_operator(char *input, int i, t_token **token)
{
	t_token_type	type;
	int				op_length;
	char			*tmp_op;

	op_length = ft_get_op_length(input, i, &type);
	if (op_length > 0)
	{
		tmp_op = ft_substr(input, i, op_length);
		ft_lstadd_token_back(token, ft_lstnew_token(type, tmp_op));
		return (op_length);
	}
	return (op_length);
}

int	ft_handle_word(char *input, int i, t_token **token)
{
	char	*word;

	word = ft_get_word(input, i);
	if (word)
	{
		ft_lstadd_token_back(token, ft_lstnew_token(TOKEN_WORD, word));
		return (ft_strlen(word));
	}
	return (1);
}

t_token	*ft_token(char *input, int i)
{
	t_token	*token;
	int		op_length;

	token = NULL;
	while (input && input[i])
	{
		op_length = ft_handle_operator(input, i, &token);
		if (op_length < 0)
			return (NULL);
		else if (op_length > 0)
			i += op_length;
		else
			i += ft_handle_word(input, i, &token);
	}
	if (ft_check_next_token(token) == 1)
		return (NULL);
	return (token);
}
