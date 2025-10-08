/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:46:26 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/07 15:03:33 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

int	env(t_env *env) //a besoin du char **environ qui est pris par le main apres argc et argv
{
	int	i;

	i = 0;
	if (!env->export)
		return (1);
	while (env->export[i])
	{
		printf("%s\n", env->export[i]);
		i++;
	}
	return (0);
}

char	**ft_env(char **environ)
{
	int	i;
	int	length;
	char **env_copy;

	length = 0;
	i = 0;
	while (environ[length])
		length++;
	env_copy = ft_malloc(sizeof(char *) * (length + 1), 0);
	while (i != length)
	{
		env_copy[i] = ft_malloc(sizeof(char) * (ft_strlen(environ[i]) + 1), 0);
		ft_strlcpy(env_copy[i], environ[i], ft_strlen(environ[i]) + 1);
		i++;
	}
	env_copy[i] = NULL;
	up_shell_level(env_copy);
	return (env_copy);
}

void up_shell_level(char **env)
{
	int	i;
	int	lvl;
	char *itoa;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(&env[i][6]) + 1;
			//free(env[i]);
			itoa = ft_itoa(lvl);
			env[i] = ft_strjoin("SHLVL=", itoa);
			//free(itoa);
			return ;
		}
		i++;
	}
}

void	ft_exit(t_env *env)
{
	//free_env(env);
	rl_clear_history();
	ft_malloc(0, 1);
	exit(0);
}

// void free_env(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (env->export[i])
// 	{
// 		//free(env->export[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (env->local_env[i])
// 	{
// 		//free(env->local_env[i]);
// 		i++;
// 	}
// 	//free(env);
// }
