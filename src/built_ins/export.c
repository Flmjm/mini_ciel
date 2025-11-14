/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:43 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/14 13:36:27 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

t_env_local	*ft_lstnew_env(char *var);
void	ft_lstadd_env_back(t_env_local **lst, t_env_local *new);

void    ft_export(t_env *env, t_commands *cmds)
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
            printf("declare -x %s\n", env->global[i]);
            i++;
        }
		i = 0;
		while (current)
		{
			printf("declare -x %s\n", current->value);
            current = current->next;
		}
    }
    else
    {
		i = 1;
		while (cmds->argv[i])
        {
			while (env->global[j])
            {
				if (ft_strncmp(env->global[j], cmds->argv[i], ft_strlen_var(cmds->argv[i])) == 0)
                {
					is_already_global = 1;
                    if (env->global[j][ft_strlen_var(cmds->argv[i])] && env->global[j][ft_strlen_var(cmds->argv[i])] == '=')
                	{
						if (cmds->argv[i][ft_strlen_var(cmds->argv[i])] == '=')
						{
							buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
							ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
							env->global[j] = buffer;
						}
						// else
						// {
						// 	buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
						// 	ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
						// 	ft_lstadd_env_back(&env->local, ft_lstnew_env(buffer));
						// 	env->global[j][0] = '\0';

						// 	// t_env_local *current = env->local;
						// 	// while (current->next)
						// 	// {
						// 	// 	printf("DEBUG %p %s\n",current, current->value);
						// 	// 	current = current->next;
						// 	// }
						// }
					}
                }
                j++;
            }
			if (is_already_global == FALSE)
			{
				buffer = ft_malloc(sizeof(char) * (ft_strlen(cmds->argv[i]) + 1), 0);
				ft_strlcpy(buffer, cmds->argv[i], ft_strlen(cmds->argv[i]) + 1);
				ft_lstadd_env_back(&env->local, ft_lstnew_env(buffer));
			}
			else
				is_already_global = FALSE;

            j = 0;
            i++;
        }
    }
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

t_env_local	*ft_lstnew_env(char *var)
{
	t_env_local	*new;

	new = ft_malloc(sizeof(new), 0);
	if (!new)
		return (NULL);
	new->value = ft_malloc(sizeof(char) * (ft_strlen(var) + 1), 0);
	ft_strlcpy(new->value, var, ft_strlen(var) + 1);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_env_back(t_env_local **lst, t_env_local *new)
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
	{
		if (ft_strlen_var(new->value) >= ft_strlen_var(last->value) && ft_strncmp(new->value, last->value, ft_strlen_var(last->value)) == 0)
		{
			last->value = new->value;
			return ;
		}
		else if (ft_strlen_var(new->value) <= ft_strlen_var(last->value) && ft_strncmp(new->value, last->value, ft_strlen_var(new->value)) == 0)
		{
			last->value = new->value;
			return ;
		}
		last = last->next;
	}
	if (ft_strlen_var(new->value) >= ft_strlen_var(last->value) && ft_strncmp(new->value, last->value, ft_strlen_var(last->value)) == 0)
	{
		last->value = new->value;
		return ;
	}
	else if (ft_strlen_var(new->value) <= ft_strlen_var(last->value) && ft_strncmp(new->value, last->value, ft_strlen_var(new->value)) == 0)
	{
		last->value = new->value;
		return ;
	}
	last->next = new;
}
