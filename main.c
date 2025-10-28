/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/28 17:02:06 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"
#include "exec/pipex_bonus.h"

int	main(int argc, char **argv, char **environt)
{
	int	exit_status;
	t_env *env_s;

	env_s = ft_malloc(sizeof(t_env), 0);
	env_s->export = ft_env(environt, env_s);
	env_s->local_env = ft_env(environt, env_s);	//sert a init la struct et a avoir une copie des variables d'environnement
	prompt_loop(env_s); //la boucle principal du shell
	return (0);
}

void	prompt_loop(t_env *env_s)
{
	t_commands *cmds;
	char 		*input;
	char 		*buffer;
	t_exitcode *exit_code;

	exit_code = ft_malloc(sizeof(t_exitcode), 0);
	exit_code->last_cmd = 0;

	while (1)
	{
		// printf("DEBUG PWD ACTUEL REEL: %s\n", env_s->pwd);
		input = readline(prompt_sentence(env_s));
		// input = ft_malloc(sizeof(char) * (ft_strlen(buffer) + 1), 0);
		// ft_strlcpy(input, buffer, ft_strlen(buffer) + 1);
		cmds = manage_input(input, exit_code);	//j'ai mis ft_token a l'interieur
		//free input dans expand var pour eviter de free des trucs utiles
		// free(input);
		//if (cmds)
			//exec_main(cmds, env_s, exit_code);
		// if (ft_strncmp(input, "exit", ft_strlen(input)) == 0) //temporaire -------
		// {	
		// 	free(input);
		// 	ft_exit(env_s, 0);
		// }
	}
}

char	*prompt_sentence(t_env *env)
{
	char	*result;
	int		i;
	char	*bblue;

	i = 5;
	result = ft_malloc(sizeof(int) * (ft_strlen(env->pwd) - 1), 0);
	// printf("DEBUG TAILLE ENVPWD: %d\n", ft_strlen(env->pwd));
	while(env->pwd[i])
	{
		result[i - 5] = env->pwd[i];
		i++;
	}
	result[i - 5] = '~';
	i++;
	result[i - 5] = '>';
	i++;
	result[i - 5] = '\0';
	bblue = ft_malloc(sizeof(int) * (ft_strlen(result) + 20), 0);


	return(result);
}
