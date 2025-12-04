/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:29:47 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/04 14:32:15 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"
#include "../../include/lib_exec.h"

int	ft_length_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

char	**add_basic_env(char **env_copy)
{
	env_copy = ft_malloc(sizeof(char *) * (4), 0);
	env_copy[3] = NULL;
	env_copy[0] = ft_malloc(sizeof(char) * (ft_strlen("OLDPWD=") + 1), 0);
	env_copy[0][0] = 0;
	ft_strlcat(env_copy[0], "OLDPWD=", ft_strlen("OLDPWD=") + 1);
	env_copy[1] = ft_malloc(sizeof(char) * (ft_strlen("PWD=") + 1), 0);
	env_copy[1][0] = 0;
	ft_strlcat(env_copy[1], "PWD=", ft_strlen("PWD=") + 1);
	env_copy[2] = ft_malloc(sizeof(char) * (ft_strlen("SHLVL=1") + 1), 0);
	env_copy[2][0] = 0;
	ft_strlcat(env_copy[2], "SHLVL=1", ft_strlen("SHLVL=1") + 1);
	return (env_copy);
}
