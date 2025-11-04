/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_next_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:09:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/04 11:46:28 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void	ft_check_next_token_heredoc(t_token *token)
{
	if (token->next->type >= 1 && token->next->type <= 5)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		exit(2);
	}
	else if (token->next->type == 0)
		token->next->type = TOKEN_EOF;
}

void	ft_check_next_token_herestring(t_token *token)
{
	if ((token->next->type >= 1 && token->next->type <= 5)
		|| token->next->type == 7)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		exit(2);
	}
	else
	{
		ft_printf("<<<: here_string not supported\n");
		exit(2);
	}
}

void	ft_check_next_token_pipe(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->value);
		exit(2);
	}
	else if (token->prev->type != TOKEN_WORD && token->prev->type != TOKEN_EOF)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->value);
		exit(2);
	}
}

void	ft_check_next_token_redir_in(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		exit(2);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		exit(2);
		;
	}
	else if (token->next->type == TOKEN_WORD && access(token->next->value,
			F_OK) != 0)
	{
		ft_printf("%s: No such file or directory\n", token->next->value);
		exit(1);
	}
	else if (token->next->type == TOKEN_WORD && access(token->next->value,
			F_OK) == 0)
	{
		return ;
	}
	else
		ft_printf("unexpected error while checking next token\n");
}

void	ft_check_next_token_redir_out(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		exit(2);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n",
			token->next->value);
		exit(2);
	}
	else if (token->next->type == TOKEN_WORD)
	{
		return ;
	}
	else
		ft_printf("unexpected error while checking next token\n");
}
