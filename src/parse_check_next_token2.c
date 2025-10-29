/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_next_token2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:09:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/29 11:40:02 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void	ft_check_next_token_redir_append(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		//exit_with_message_and_//free("syntax error near unexpected token 'newline'\n", token, 2);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->next->value);
		// exit_with_message_and_//free(NULL, token, 2);
	}
	else if (token->next->type == TOKEN_WORD)
	{
		return ;
	}
	else
		ft_printf("unexpected error while checking next token\n");
}

void	ft_check_next_token(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == TOKEN_HERESTRING)
			ft_check_next_token_herestring(token);
		else if (token->type == TOKEN_HEREDOC)
			ft_check_next_token_heredoc(token);
		else if (token->type == TOKEN_PIPE)
			ft_check_next_token_pipe(token);
		else if (token->type == TOKEN_REDIRECT_IN)
			ft_check_next_token_redir_in(token);
		else if (token->type == TOKEN_REDIRECT_OUT)
			ft_check_next_token_redir_out(token);
		else if (token->type == TOKEN_REDIRECT_APPEND)
			ft_check_next_token_redir_append(token);
		token = token->next;
	}
}
