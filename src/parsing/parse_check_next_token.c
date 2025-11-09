/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_next_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:09:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/09 21:11:08 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

int	ft_check_next_token_heredoc(t_token *token)
{
	if (!token->next)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		return(1);
	}
	if (token->next->type >= 1 && token->next->type <= 5 || token->next->type == 7)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		return(1);
	}
	else if (token->next->type == 0)
		token->next->type = TOKEN_EOF;
	return(0);
}

int	ft_check_next_token_herestring(t_token *token)
{
	if ((token->next->type >= 1 && token->next->type <= 5)
		|| token->next->type == 7)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		return(1);
	}
	else
	{
		ft_printf("<<<: here_string not supported\n");
		return(1);
	}
}

int	ft_check_next_token_pipe(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->value);
		return(1);
	}
	else if (token->prev->type != TOKEN_WORD && token->prev->type != TOKEN_EOF)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->value);
		return(1);
	}
	return(0);
}

int	ft_check_next_token_redir_in(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		return(1);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		return(1);
	}
	else if (token->next->type == TOKEN_WORD)
		return (0);
	else
	{
		ft_printf("unexpected error while checking next token\n");
		return(1);
	}
}

int	ft_check_next_token_redir_out(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		return(1);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		return(1);
	}
	else if (token->next->type == TOKEN_WORD)
		return (0);
	else
	{
		ft_printf("unexpected error while checking next token\n");
		return(1);
	}
}
