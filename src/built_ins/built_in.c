/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:46:26 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/19 16:47:13 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"
#include "../../include/lib_exec.h"

int	env_built_in(t_env *env)
{
	int	i;

	i = 0;
	if (!env->global)
		return (1);
	while (env->global[i])
	{
		if (env->global[i][ft_strlen_var(env->global[i])] == '=')
			ft_printf("%s\n", env->global[i]);
		i++;
	}
	return (0);
}

char	**ft_env(char **environ, t_env *env)
{
	int		i;
	int		length;
	char	**env_copy;

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

char	**add_var(char *new_var, t_env *env)
{
	int		i;
	int		length;
	char	**env_copy;

	length = 0;
	i = 0;
	while (env->global[length])
		length++;
	env_copy = ft_malloc(sizeof(char *) * (length + 2), 0);
	while (i != length)
	{
		env_copy[i] = ft_malloc(sizeof(char)
				* (ft_strlen(env->global[i]) + 1), 0);
		ft_strlcpy(env_copy[i], env->global[i], ft_strlen(env->global[i]) + 1);
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

void	up_shell_level(char **env)
{
	int		i;
	int		lvl;
	char	*itoa;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(&env[i][6]) + 1;
			itoa = ft_itoa(lvl);
			env[i] = ft_strjoin("SHLVL=", itoa);
			return ;
		}
		i++;
	}
}
