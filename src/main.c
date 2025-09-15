/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/15 22:48:03 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

int	main(int argc, char **argv, char **environt)
{
	int	exit_status;
	char *input;
	t_env *env;

	env = malloc(sizeof(t_env));
	env->env_ = environt;
	ft_env(env);	//important sert a init la struct et a avoir une copie des variables d'environnement

	exit_status = 0;


	while (exit_status != 1)
	{
		input = readline(PROMPT_LINE);
		manage_input(input);	//j'ai mis ft_token a l'interieur jsp trop 🥸

		if (ft_strncmp(input, "exit", 4) == 0)
			exit_status = 1;
		free(input);
	}
	rl_clear_history();

	return (0);
}

void	ft_env(t_env *env)
{
	int	i;
	int	length;
	char **env_copy;

	length = 0;
	i = 0;
	while (env->env_[length])
		length++;
	env_copy = malloc(sizeof(char *) * (length + 1));
	while (i != length)
	{
		env_copy[i] = malloc(sizeof(char) * (ft_strlen(env->env_[i]) + 1));
		ft_strlcpy(env_copy[i], env->env_[i], ft_strlen(env->env_[i]));
		i++;
	}
	env_copy[i] = NULL;
	env->env = env_copy;
}
