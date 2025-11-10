/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:37:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/10 14:32:47 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

int	count_words(t_token *token)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = token;
	while (curr && curr->type != TOKEN_PIPE)
	{
		while (curr && (curr->type >= TOKEN_REDIRECT_IN
				&& curr->type <= TOKEN_EOF))
			curr = curr->next;
		while (curr && curr->type == TOKEN_WORD)
		{
			if (curr->prev == NULL || curr->prev->type == TOKEN_WORD
				|| curr->prev->type == TOKEN_PIPE
				|| curr->prev->type == TOKEN_EOF)
				count++;
			curr = curr->next;
		}
	}
	return (count);
}

t_commands	*ft_lstnew_command(int words)
{
	t_commands	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	if (words == 0)
	{
		new->argv = ft_malloc(2 * sizeof(char *), 0);
		new->argv[0] = NULL;
	}
	else
		new->argv = ft_malloc((words + 1) * sizeof(char *), 0);
	new->redirect = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_cmd_back(t_commands **lst, t_commands *new)
{
	t_commands	*last;

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

static t_token *ft_process_node(t_token *token, t_commands *node)
{
	t_token		*tmp_token;
	int	i;

	tmp_token = token;
	i = 0;
	while (tmp_token && tmp_token->type != TOKEN_PIPE)
	{
		if (tmp_token->type == TOKEN_EOF)
			tmp_token = tmp_token->next;
		else if (tmp_token->type >= TOKEN_REDIRECT_IN
			&& tmp_token->type <= TOKEN_HERESTRING)
			tmp_token = ft_add_redir(tmp_token, node);
		else if (tmp_token->type == TOKEN_WORD)
		{
			node->argv[i] = ft_strdup(tmp_token->value);
			i++;
			tmp_token = tmp_token->next;
		}
		else
			tmp_token = tmp_token->next;
	}
	node->argv[i] = NULL;
	if (tmp_token && tmp_token->type == TOKEN_PIPE)
		tmp_token = tmp_token->next;
	return(tmp_token);
}

t_commands	*ft_init_cmd(t_token *token)
{
	t_commands	*command;
	int			i;
	int			cmd_count;
	t_commands	*node;

	cmd_count = 0;
	command = NULL;
	while (token)
	{
		cmd_count = count_words(token);
		node = ft_lstnew_command(cmd_count);
		if (!node)
			return(command);
		token = ft_process_node(token, node);
		ft_lstadd_cmd_back(&command, node);
	}
	return (command);
}

