/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:15:52 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/17 00:11:11 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

int	ft_pwd(t_env *env)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
	{
		if (env->pwd)
		{
			ft_putendl_fd(env->pwd, 1);
			return (0);
		}
		return (1);
	}
	ft_putendl_fd(buf, 1);
	return (0);
}
