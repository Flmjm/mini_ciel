/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:55:23 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/03 11:20:51 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

void	write_var(t_env *env, int i, int j)
{
	int	end;

	end = 0;
	while (env->global[i][j])
	{
		write(1, &env->global[i][j], 1);
		if (env->global[i][j] == '=' && j == ft_strlen_var(env->global[i]))
		{
			write(1, "\"", 1);
			end = 1;
		}
		if (env->global[i][j + 1] == '\0' && end == 1)
			write(1, "\"", 1);
		j++;
	}
}

int	error_in_export_arg(t_commands *cmds, int i, t_env *env)
{
	ft_putstr_fd(cmds->argv[0], 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(cmds->argv[i], 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	env->exitcode->last_cmd = 1;
}
