/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/19 16:47:05 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

static int	is_var_name_valid(char *var);

static int	update_var(t_commands *cmds, int i, int j, t_env *env)
{
	if (cmds->argv[i][ft_strlen_var(cmds->argv[i])] == '=')
		env->global[j] = cmds->argv[i];
	return (1);
}

static void	add_var_to_env(t_commands *cmds, t_env *env, int i)
{
	char	*buffer;

	buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
	ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
	env->global = add_var(buffer, env);
}

static int	export_with_arg(t_commands *cmds, t_env *env, int i, int j)
{
	int	is_already_global;

	i = 1;
	while (cmds->argv[i])
	{
		is_already_global = FALSE;
		while (env->global[j])
		{
			if (ft_strncmp(env->global[j], cmds->argv[i]
					, ft_strlen_var(env->global[j])) == 0)
				is_already_global = update_var(cmds, i, j, env);
			j++;
		}
		if (is_already_global == FALSE && is_var_name_valid(cmds->argv[i]) == 0)
			add_var_to_env(cmds, env, i);
		if (is_var_name_valid(cmds->argv[i]) == 1)
			return (1);
		j = 0;
		i++;
	}
}

int	ft_export(t_env *env, t_commands *cmds)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!cmds->argv[1])
	{
		while (env->global[i])
		{
			if (env->global[i][0])
				ft_printf("declare -x %s\n", env->global[i]);
			i++;
		}
	}
	else
	{
		if (cmds->next)
			return (0);
		return (export_with_arg(cmds, env, i, j));
	}
	return (0);
}

static int	is_var_name_valid(char *var)
{
	int	i;

	i = 1;
	if ((ft_isdigit(var[0]) && var[0] != '_') || var[0] == '=')
		return (1);
	while (var[i] && i < ft_strlen_var(var))
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
