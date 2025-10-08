/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:55 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/08 16:53:41 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

t_infiles	*ft_lstnew_redirect_in(char *filename)
{
	t_infiles	*new;

	new = ft_malloc(sizeof(t_redirect), 0);
	if (!new)
		return (NULL);
	new->infile = filename;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

t_outfiles	*ft_lstnew_redirect_out(char *filename, t_file_type type)
{
	t_outfiles	*new;

	new = ft_malloc(sizeof(t_redirect), 0);
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
