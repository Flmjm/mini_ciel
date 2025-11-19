/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:46:21 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/16 23:13:43 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_malloc(size_t size, int param)
{
	static t_list	**list = NULL;
	void			*result;

	if (param == 1)
	{
		delete_all(list);
		free(list);
		list = NULL;
		return (NULL);
	}
	result = malloc(size);
	if (!result)
		return (NULL);
	if (!list)
	{
		list = malloc(sizeof(t_list *));
		*list = NULL;
		init_lst(list, result);
	}
	else
		make_malloc(result, list);
	return (result);
}

void	*delete_all(t_list **head)
{
	t_list	*current;
	t_list	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
	return (NULL);
}
