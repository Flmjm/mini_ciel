/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/21 00:26:55 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"
#include "exec/pipex_bonus.h"

int	main(int argc, char **argv, char **environt)
{
	int	exit_status;
	char *input;
	t_env *env_s;

	env_s = ft_malloc(sizeof(t_env), 0);
	env_s->export = ft_env(environt, env_s);
	env_s->local_env = ft_env(environt, env_s);	//sert a init la struct et a avoir une copie des variables d'environnement
	prompt_loop(input, env_s); //la boucle principal du shell
	return (0);
}

void	prompt_loop(char *input, t_env *env_s)
{
	t_commands *cmds;

	while (1)
	{
		input = readline(PROMPT_LINE);
		cmds = manage_input(input);	//j'ai mis ft_token a l'interieur
		if (cmds)
			exec_main(cmds, env_s);

		// if (ft_strncmp(input, "exit", ft_strlen(input)) == 0) //temporaire -------
		// 	ft_exit(env_s);
		// else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		// 	env(env_s);
		// else if (ft_strncmp(input, "export", ft_strlen(input)))
			// export()
		//--------------------------------------------------------------------------
		//free(input);
	}
}
