/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:41:30 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/11 13:18:41 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

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

int	ft_is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '>' || c == '<' || c == '&'
		|| c == ';')
		return (1);
	return (0);
}

int	get_op_redir_in(char *input, int i, t_token_type *type)
{
	if (input[i + 1] == '<' && input[i + 2] == '<')
	{
		*type = TOKEN_HERESTRING;
		return (3);
	}
	else if (input[i + 1] == '<')
	{
		*type = TOKEN_HEREDOC;
		return (2);
	}
	*type = TOKEN_REDIRECT_IN;
	return (1);
}

int	ft_get_op_length(char *input, int i, t_token_type *type)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|' || input[i - 1] == '|')
			return (-1);
		*type = TOKEN_PIPE;
		return (1);
	}
	else if (input[i] == '<')
		return (get_op_redir_in(input, i, type));
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
