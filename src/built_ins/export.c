/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/16 01:22:56 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

static int	is_var_name_valid(char *var);

int    ft_export(t_env *env, t_commands *cmds)
{
    int i;
    int j;
	int	is_already_global;
	t_env_local	*current;
	char *buffer;

	current = env->local;
	is_already_global = FALSE;
    j = 0;
    i = 0;
    if (!cmds->argv[1])
    {
        while (env->global[i])
        {
			if (env->global[i][0])
            	printf("declare -x %s\n", env->global[i]);
            i++;
        }
    }
    else
    {
		if (cmds->next)
			return (0);
		i = 1;
		while (cmds->argv[i])
        {
			while (env->global[j])
            {
				if (ft_strncmp(env->global[j], cmds->argv[i], ft_strlen_var(env->global[j])) == 0)
                {
					is_already_global = 1;
					if (cmds->argv[i][ft_strlen_var(cmds->argv[i])] == '=')
                    	env->global[j] = cmds->argv[i];
                }
                j++;
            }
			if (is_already_global == FALSE && is_var_name_valid(cmds->argv[i]) == 0)
			{
				buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
				ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
				env->global = add_var(buffer, env);
			}
			if (is_var_name_valid(cmds->argv[i]) == 1)
				return (1);
			is_already_global = FALSE;
            j = 0;
            i++;
        }
    }
	return (0);
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