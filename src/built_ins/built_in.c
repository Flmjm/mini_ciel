/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:46:26 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/11 20:23:45 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"
#include "../../include/lib_exec.h"

int	env_built_in(t_env *env) //a besoin du char **environ qui est pris par le main apres argc et argv
{
	int	i;

	i = 0;
	if (!env->global)
		return (1);
	while (env->global[i])
	{
		printf("%s\n", env->global[i]);
		i++;
	}
	return (0);
}

char	**ft_env(char **environ, t_env *env)
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
		if (ft_strncmp("OLDPWD=", env_copy[i], 7) == 0)
			env->oldpwd = env_copy[i] + 7;
		else if (ft_strncmp("PWD=", env_copy[i], 4) == 0)
			env->pwd = env_copy[i] + 4;
		i++;
	}
	env_copy[i] = NULL;
	up_shell_level(env_copy);
	return (env_copy);
}

void	add_var(char **environ, char *new_var, t_env *env)
{
	int	i;
	int	length;
	char **env_copy;
	
	length = 0;
	i = 0;
	while (environ[length])
		length++;
	env_copy = ft_malloc(sizeof(char *) * (length + 2), 0);
	while (i != length)
	{
		env_copy[i] = ft_malloc(sizeof(char) * (ft_strlen(environ[i]) + 1), 0);
		ft_strlcpy(env_copy[i], environ[i], ft_strlen(environ[i]) + 1);
		if (ft_strncmp("OLDPWD=", env_copy[i], 7) == 0)
			env->oldpwd = env_copy[i] + 7;
		else if (ft_strncmp("PWD=", env_copy[i], 4) == 0)
			env->pwd = env_copy[i] + 4;
		i++;
	}
	env_copy[i] = new_var;
	env_copy[i + 1] = NULL;
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
