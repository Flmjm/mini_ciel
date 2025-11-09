/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:41:30 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/20 16:41:49 by jmalaval         ###   ########.fr       */
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
