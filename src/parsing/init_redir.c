/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:55 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/10 10:45:16 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

t_redirect	*ft_lstnew_redirect(char *filename, t_file_type type, char *word)
{
	t_redirect	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	if (type == FILE_REDIRECT_IN)
		new->type = FILE_REDIRECT_IN;
	else if (type == FILE_HEREDOC)
		new->type = FILE_HEREDOC;
	else if (type == FILE_REDIRECT_OUT)
		new->type = FILE_REDIRECT_OUT;
	else if (type == FILE_REDIRECT_APPEND)
		new->type = FILE_REDIRECT_APPEND; 
	new->word_eof = word;
	new->filename = filename;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_redirect_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

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

t_token	*ft_add_redir(t_token *token, t_commands *node)
{
	while (token && (token->type == TOKEN_REDIRECT_IN
			|| token->type == TOKEN_REDIRECT_OUT
			|| token->type == TOKEN_REDIRECT_APPEND
			|| token->type == TOKEN_HEREDOC))
	{
		if (token->type == TOKEN_REDIRECT_IN)
			ft_lstadd_redirect_back(&node->redirect,
				ft_lstnew_redirect(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_IN, NULL));
		else if (token->type == TOKEN_REDIRECT_OUT)
			ft_lstadd_redirect_back(&node->redirect,
				ft_lstnew_redirect(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_OUT, NULL));
		else if (token->type == TOKEN_REDIRECT_APPEND)
			ft_lstadd_redirect_back(&node->redirect,
				ft_lstnew_redirect(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_APPEND, NULL));
		else if (token->type == TOKEN_HEREDOC)
			ft_lstadd_redirect_back(&node->redirect, ft_lstnew_redirect(NULL,
					FILE_HEREDOC, ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0)));
		token = token->next->next;
	}
	return (token);
}
