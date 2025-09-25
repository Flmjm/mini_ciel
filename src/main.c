/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/25 12:25:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

int	main(int argc, char **argv, char **environt)
{
	int	exit_status;
	char *input;
	t_env *env_s;

	env_s = ft_malloc(sizeof(t_env), 0);
	env_s->export = ft_env(environt);
	env_s->local_env = ft_env(environt);	//sert a init la struct et a avoir une copie des variables d'environnement

	prompt_loop(input, env_s); //la boucle principal du shell

	return (0);
}

void	prompt_loop(char *input, t_env *env_s)
{
	while (1)
	{
		input = readline(PROMPT_LINE);
		manage_input(input);	//j'ai mis ft_token a l'interieur

		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0) //temporaire -------
			ft_exit(env_s);
		// else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		// 	env(env_s);
		// else if (ft_strncmp(input, "export", ft_strlen(input)))
			// export()
		//--------------------------------------------------------------------------
		//free(input);
	}
}
