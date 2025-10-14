/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_next_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:09:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/14 14:29:49 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

// void	recall_readline(t_token *infos)
// {
// 	char	*buffer;
// 	char	*temp_input;

// 	temp_input = readline(">");
// 	if (ft_strlen(temp_input) == 0)
// 		return ;
// 	buffer = ft_malloc(sizeof(char) * ft_strlen(infos->value));
// 	ft_strlcpy(buffer, infos->value, ft_strlen(infos->value) + 1);
// 	//free(infos->value);
// 	infos->value = ft_malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(temp_input) + 1));
// 	ft_strlcpy(infos->value, buffer, (ft_strlen(buffer) + ft_strlen(temp_input)));
// 	//free(buffer);
// 	ft_strlcat(infos->value, temp_input, ft_strlen(infos->value) + ft_strlen(temp_input) + 1);
// 	//free(temp_input);
// }

void	ft_check_next_token_heredoc(t_token *token)
{
	if (token->next->type >= 1 && token->next->type <= 5)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->next->value);
		// exit_with_message_and_//free(NULL, token, 2);
	}
	else if (token->next->type == 0)
		token->next->type = TOKEN_EOF;
}

void	ft_check_next_token_herestring(t_token *token)
{
	if ((token->next->type >= 1 && token->next->type <= 5) || token->next->type == 7)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->next->value);
		// exit_with_message_and_//free(NULL, token, 2);
		// exit(2);
	}
	else
	{
		ft_printf("<<<: here_string not supported\n");
		// exit_with_message_and_//free(NULL, token, 2);
		// exit(2);
	}
}

void	ft_check_next_token_pipe(t_token *token)
{
	if (token->next == NULL)
		{
            ft_printf("TEST A SUPPRIMER !!! renvoie le prompt en attendant\n"); // renvoie le prompt et attend une commande
            //recall_readline(token);
        }
	else if (token->prev->type != TOKEN_WORD && token->prev->type != TOKEN_EOF)
	{
		printf("token type prev : %d\n", token->prev->type);
		ft_printf("syntax error near unexpected token '%s'\n", token->value);
		// exit_with_message_and_//free(NULL, token, 2);
	}
}

void	ft_check_next_token_redir_in(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		// exit_with_message_and_//free("syntax error near unexpected token 'newline'\n", token, 2);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near unexpected token '%s'\n", token->next->value);
		// exit_with_message_and_//free(NULL, token, 2);
	}
    else if (token->next->type == TOKEN_WORD && access(token->next->value, F_OK) != 0)
    {
        ft_printf("%s: No such file or directory\n", token->next->value);
        // exit_with_message_and_//free(NULL, token, 1);
    }
	else if (token->next->type == TOKEN_WORD && access(token->next->value, F_OK) == 0)
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
		// exit_with_message_and_//free("syntax error near unexpected token 'newline'\n", token, 2);
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

void	ft_check_next_token_redir_append(t_token *token)
{
	if (token->next == NULL)
	{
		ft_printf("syntax error near unexpected token 'newline'\n");
		// exit_with_message_and_//free("syntax error near unexpected token 'newline'\n", token, 2);
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
