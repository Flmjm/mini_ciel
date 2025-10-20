/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:01:46 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/07 15:03:14 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void	exit_with_message_and_free(char *str, t_token *token, int n)
{
	if (str)
		ft_putendl_fd(str, 2);
	ft_free_tokens(token);
	// exit(n);
}

void    ft_free_tokens(t_token *tokens)
{
    t_token *curr;

    if (!tokens)
        return;
    while (tokens)
    {
        curr = tokens->next;
        // free(tokens->value);
        // free(tokens);
        tokens = curr;
    }
}
