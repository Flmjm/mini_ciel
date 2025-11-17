/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:37:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/17 01:19:41 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

static char	**delete_var(t_env *env, char *var);

int	ft_unset(t_env *env, t_commands *cmds)
{
	int	i;

	i = 1;
	if (!cmds->argv[i])
		return (0);
	while (cmds->argv[i])
	{
		env->global = delete_var(env, cmds->argv[i]);
		i++;
	}
	return (0);
}

static char	**delete_var(t_env *env, char *var)
{
	int		i;
	int		j;
	int		length;
	char	**env_copy;

	length = 0;
	j = 0;
	i = 0;
	while (env->global[length])
		length++;
	env_copy = ft_malloc(sizeof(char *) * (length + 2), 0);
	while (j != length)
	{
		if (ft_strncmp(env->global[j], var, ft_strlen_var(env->global[j])) != 0)
		{
			env_copy[i] = ft_malloc(sizeof(char)
					* (ft_strlen(env->global[j]) + 1), 0);
			ft_strlcpy(env_copy[i], env->global[j],
				ft_strlen(env->global[j]) + 1);
			i++;
		}
		j++;
	}
	env_copy[i + 1] = NULL;
	return (env_copy);
}

int	ft_strlen_var(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
