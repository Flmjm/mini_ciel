/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/11 22:32:53 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

static int	ft_strlen_var(const char *str);

void    ft_export(t_env *env, t_commands *cmds)
{
    int i;
    int j;
    
    j = 0;
    i = 0;
    if (!cmds->argv[1])
    {
        while (env->global[i])
        {
            printf("declare -x %s\n", env->global[i]);
            i++;
        }
    }
    else
    {
        while (cmds->argv[i])
        {
            while (env->global[j])
            {
                if (ft_strncmp(env->global[j], cmds->argv[i], ft_strlen(cmds->argv[i])) == 0)
                {
                    if (env->global[j][ft_strlen(cmds->argv[i]) + 1] && env->global[j][ft_strlen(cmds->argv[i])] == '=')
                        printf("%s %s\n", env->global[j], cmds->argv[i]);
                }
                j++;
            }
            j = 0;
            i++;
        }
    }
}

static int	ft_strlen_var(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
        i++;
	return (i);
}