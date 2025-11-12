/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/12 20:01:28 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

static int	ft_strlen_var(const char *str);
t_env_local	*ft_lstnew_env(char *var);
t_env_local	ft_lstadd_env_back(t_env_local **lst, t_env_local *new);

void    ft_export(t_env *env, t_commands *cmds)
{
    int i;
    int j;
	char *buffer;

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
                if (ft_strncmp(env->global[j], cmds->argv[i], ft_strlen_var(cmds->argv[i])) == 0)
                {
                    if (env->global[j][ft_strlen_var(cmds->argv[i])] && env->global[j][ft_strlen_var(cmds->argv[i])] == '=')
                	{
						if (cmds->argv[i][ft_strlen_var(cmds->argv[i]) + 1])
						{
							printf("ALED %s %s\n", env->global[j], cmds->argv[i]);
							buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
							ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
							env->global[j] = buffer;
							printf("ALED %s %s\n", env->global[j], cmds->argv[i]);
						}
						else
						{
							buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
							ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
							// ft_lstadd_back(&env->local, buffer);
							ft_lstnew_env(cmds->argv[i]);  // c ca trou de balle qui vas pas
							// t_list *current = env->local;
							// while (current->next)
							// {
							// 	printf("DEBUG %s\n", *current->content);
							// 	current = current->next;
							// }
						}
					}
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

t_env_local	*ft_lstnew_env(char *var)
{
	t_env_local	*new;

	new = ft_malloc(sizeof(new), 0);
	if (!new)
		return (NULL);
	new->value = ft_malloc(sizeof(char) * (ft_strlen(var) + 1), 0);
	ft_strlcpy(new, var, ft_strlen(var) + 1);
	printf("DEBUG: %s\n", new->value);
	new->next = NULL;
	return (new);
}

t_env_local	ft_lstadd_env_back(t_env_local **lst, t_env_local *new)
{
	t_env_local	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}
