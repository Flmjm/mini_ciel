/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/15 23:53:44 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

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
		i = 1;
		while (cmds->argv[i])
        {
			while (env->global[j])
            {
				if (ft_strncmp(env->global[j], cmds->argv[i], ft_strlen_var(env->global[j])) == 0)
                {
					printf("DEBUG: %s\n", env->global[j]);
					is_already_global = 1;
					if (cmds->argv[i][ft_strlen_var(cmds->argv[i])] == '=')
                    	env->global[j] = cmds->argv[i];
					printf("ALED 1\n");
                }
                j++;
            }
			if (is_already_global == FALSE)
			{
				buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
				ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
				env->global = add_var(buffer, env);
				printf("ALED 2\n");
			}
			else
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
