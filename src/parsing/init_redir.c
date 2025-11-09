/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:55 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/08 11:39:21 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

t_infiles	*ft_lstnew_redirect_in(char *filename, t_file_type type, char *word)
{
	t_infiles	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	if (type == FILE_REDIRECT_IN)
		new->type = FILE_REDIRECT_IN;
	else if (type == FILE_HEREDOC)
		new->type = FILE_HEREDOC;
	new->word_eof = word;
	new->infile = filename;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

t_outfiles	*ft_lstnew_redirect_out(char *filename, t_file_type type)
{
	t_outfiles	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	new->outfile = filename;
	if (type == FILE_REDIRECT_OUT)
		new->type = FILE_REDIRECT_OUT;
	else if (type == FILE_REDIRECT_APPEND)
		new->type = FILE_REDIRECT_APPEND;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_infiles_back(t_infiles **lst, t_infiles *new)
{
	t_infiles	*last;

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

void	ft_lstadd_outfiles_back(t_outfiles **lst, t_outfiles *new)
{
	t_outfiles	*last;

	last = NULL;
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
			ft_lstadd_infiles_back(&node->infiles,
				ft_lstnew_redirect_in(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_IN, NULL));
		else if (token->type == TOKEN_REDIRECT_OUT)
			ft_lstadd_outfiles_back(&node->outfiles,
				ft_lstnew_redirect_out(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_OUT));
		else if (token->type == TOKEN_REDIRECT_APPEND)
			ft_lstadd_outfiles_back(&node->outfiles,
				ft_lstnew_redirect_out(ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0), FILE_REDIRECT_APPEND));
		else if (token->type == TOKEN_HEREDOC)
			ft_lstadd_infiles_back(&node->infiles, ft_lstnew_redirect_in(NULL,
					FILE_HEREDOC, ft_check_quotes_argv(token->next->value,
						ft_strlen(token->next->value), 0, 0)));
		token = token->next->next;
	}
	return (token);
}
