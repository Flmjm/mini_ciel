/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/04 15:34:39 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

int	main(void)
{
	int	exit_status;
	char *input;

	exit_status = 0;
	while (exit_status != 1)
	{
		input = readline(PROMPT_LINE);
		ft_token(input);		// a arrêter 
		//manage_input(input);

		if (ft_strncmp(input, "exit", 4) == 0)
			exit_status = 1;
		// free(input);
	}
	rl_clear_history();
	return (0);
}


