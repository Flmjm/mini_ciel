/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_next_token2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:09:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/04 11:36:12 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

int	ft_check_next_token_redir_append(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		return(1);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->next->value);
		return(1);
	}
	else if (token->next->type == TOKEN_WORD)
	{
		return (0);
	}
	else
	{
		ft_printf("unexpected error while checking next token\n");
		return(1);
	}
}

int	ft_check_next_token(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == TOKEN_HERESTRING)
			return (ft_check_next_token_herestring(token));
		else if (token->type == TOKEN_HEREDOC)
			return(ft_check_next_token_heredoc(token));
		else if (token->type == TOKEN_PIPE)
			return(ft_check_next_token_pipe(token));
		else if (token->type == TOKEN_REDIRECT_IN)
			return(ft_check_next_token_redir_in(token));
		else if (token->type == TOKEN_REDIRECT_OUT)
			return(ft_check_next_token_redir_out(token));
		else if (token->type == TOKEN_REDIRECT_APPEND)
			return(ft_check_next_token_redir_append(token));
		token = token->next;
	}
}
