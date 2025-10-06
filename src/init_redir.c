/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:55 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/06 15:31:25 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"


t_redirect	*ft_lstnew_redirect(char *filename, t_file_type type)
{
	t_redirect	*new;

	new = ft_malloc(sizeof(t_redirect), 0);
	if (!new)
		return (NULL);
	new->filename = filename;
	if (type == FILE_REDIRECT_IN)
		new->type = FILE_REDIRECT_IN;
	else if (type == FILE_REDIRECT_OUT)
		new->type = FILE_REDIRECT_OUT;
	else if (type == FILE_REDIRECT_APPEND)
		new->type == FILE_REDIRECT_APPEND;
	new->fd = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// void	ft_init_file(t_token *token)
// {
// 	t_redirect	*file;

// 	file = ft_malloc(sizeof(t_redirect), 0);
// 	if (!file)
// 		return ;
// 	if (token->type == 0 && access(token->value, F_OK) == 0 && token->prev == NULL && token->next == NULL)
// 	{
// 		ft_printf("%s: Command not found", token->value);
// 		//exit_with_message_and_//free(NULL, token, 127);
// 	}
// 	else
// 		ft_lstadd_redirect_back(&file, ft_lstnew_redirect(token->value));
// 	//free(file); //?
// }

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
	new->prev = last;
	last->next = new;
}