/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:44:15 by jmalaval          #+#    #+#             */
/*   Updated: 2025/09/03 20:23:21 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"


// typedef enum e_token_type
// {
// 	TOKEN_WORD,            // 0 - Arguments, commandes
// 	TOKEN_PIPE,            // 1 - |
// 	TOKEN_AND,             // 2 - &&
// 	TOKEN_OR,              // 3 - ||
// 	TOKEN_REDIRECT_IN,     // 4 - <
// 	TOKEN_REDIRECT_OUT,    // 5 - >
// 	TOKEN_REDIRECT_APPEND, // 6 - >>
// 	TOKEN_HEREDOC,         // 7 - <<
// 	TOKEN_SEMICOLON,       // 8 - ;
// 	TOKEN_EOF              // 9 - Fin de ligne
// }					t_token_type;

t_token	*ft_lstnew_token(t_token_type type, char *content)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_token_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

int	ft_get_op_length(char *input, int i, t_token_type *type)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			*type = TOKEN_OR;
			return (2);
		}
		*type = TOKEN_PIPE;
		return (1);
	}
	else if (input[i] == '&' && input[i + 1] == '&')
	{
		*type = TOKEN_AND;
		return (1);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			*type = TOKEN_HEREDOC;
			return (2);
		}
		*type = TOKEN_REDIRECT_IN;
		return (1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			*type = TOKEN_REDIRECT_APPEND;
			return (2);
		}
		*type = TOKEN_REDIRECT_OUT;
		return (1);
	}
	else if (input[i] == ';')
	{
		*type = TOKEN_SEMICOLON;
		return (1);
	}
	return (0);
}

char *ft_get_word(char *input, int start)
{
    char    *word;
    int     i;
    int     in_quotes;
    char    quote;

    i = start;
    in_quotes = 0;
    word = NULL;
    while (input[i])
    {
        if (in_quotes == 0)
        {
            if (input[i] == '"' || input[i] == '\'')
            {
                in_quotes = 1;
                quote = input[i];
            }
            else if (input[i] == '|' || input[i] == '>'|| input[i] == '<'|| input[i] == '&' || input[i] == ';')
                break ;
        }
        else
        {
            if (input[i] = quote)
                in_quotes = 0;
        }
        i++;
    }
    if (i > start)
        word = ft_substr(input, start, i - start);
    return (word);
}

void	ft_token(char *input)
{
	t_token *token;
	t_token_type type;
	int op_length;
	char *tmp_op;
	int i;
	int j;
    char *word;

	i = 0;
	token = malloc(sizeof(t_token));
	while (input && input[i])
	{
		op_length = ft_get_op_length(input, i, &type);
		if (op_length > 0)
		{
			tmp_op = ft_substr(input, i, op_length);
			ft_lstadd_token_back(&token, ft_lstnew_token(type, tmp_op));
			i += op_length;
		}
		else
		{
            word = ft_get_word(input, i);
            if (word)
            {
                ft_lstadd_token_back(&token, ft_lstnew_token(TOKEN_WORD, word));
                i += ft_strlen(word);
            }
            else
			    i++;
		}
	}
}

void    ft_free_tokens(t_token *tokens)
{
    t_token *curr;
    
    while (tokens)
    {
        curr = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = curr;
    }
}

