/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:44:15 by jmalaval          #+#    #+#             */
/*   Updated: 2025/09/23 12:06:54 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

t_token	*ft_lstnew_token(t_token_type type, char *content)
{
	t_token	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	new->prev = NULL;
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
	new->prev = last;
	last->next = new;
}

int	ft_get_op_length(char *input, int i, t_token_type *type)
{
	if (input[i] == '|')
	{
		if (input[i+1] == '|' || input[i-1] == '|')
			return (-1);								// potentiellement message d'erreur sinon pas tokenisé
		*type = TOKEN_PIPE;
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
            else if (input[i] == ' ' || input[i] == '\t' || input[i] == '|' || input[i] == '>'|| input[i] == '<'|| input[i] == '&' || input[i] == ';')
                break ;
        }
        else
        {
            if (input[i] == quote)
                in_quotes = 0;
        }
        i++;
    }
    if (i > start)
        word = ft_substr(input, start, i - start);
    return (word);
}
// j'ai ajoute les espaces et \t comme fin de mot donc maintenant une commande et ses arguments peuvent etre decomposes en plusieurs tokens
// je pense qu'il faudra faire un truc du style if type == WORD et type->prev != WORD et type->next == WORD, alors c'est des arguments
// prevoir une liste doublement chainee ?
// ou alors quand type != WORD && ->next->type == WORD && ->next->next->type == WORD (c'est laborieux)

t_token	*ft_token(char *input) // '<<' segfault
{
	t_token *token;
	t_token_type type;
	int op_length;
	char *tmp_op;
	int i;
    char *word;

	i = 0;
	token = ft_malloc(sizeof(t_token), 0);
	token = NULL;
	while (input && input[i])
	{
		op_length = ft_get_op_length(input, i, &type);
		if (op_length > 0)
		{
			tmp_op = ft_substr(input, i, op_length);
			ft_lstadd_token_back(&token, ft_lstnew_token(type, tmp_op));
			i += op_length;
		}
		//else if (op_length < 0)		// signifie que on a un ||
			// exit_with_message_and_//free("syntax error near unexpected token '|'\n", token, 2); // ou on l'envoie comme un mot et cmd not found ?
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
	//ft_lstadd_token_back(&token, ft_lstnew_token(TOKEN_NEWLINE, "newline"));
	ft_check_next_token(token);
	return (token);
}


// fonction test pour voir les tokens
void print_tokens(t_token *tokens) {
    printf("\n=== TOKENS ===\n");
    t_token *current = tokens;
    int index = 0;

    while (current) {
        printf("[%d] %d: '%s'\n",
               index,
               current->type,
               current->value);
        current = current->next;
		index++;
    }
    printf("\n");
}

void print_redir(t_redirect *redirection) {
    printf("\n=== TOKENS ===\n");
    t_redirect *current = redirection;
    int index = 0;

    while (current) {
        printf("[%d] %d: '%s'\n",
               index,
               current->type,
               current->filename);
        current = current->next;
		index++;
    }
    printf("\n");
}
