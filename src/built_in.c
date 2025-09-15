/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:46:26 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/15 22:47:21 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

int	env(t_env *env) //a besoin du char **environ qui est pris par le main apres argc et argv
{
	int	i;

	i = 0;
	if (!env->env)
		return (1);
	while (env->env[i])
	{
		printf("%s\n", env->env[i]);
		i++;
	}
	return (0);
}
