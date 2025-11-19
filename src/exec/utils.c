/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/19 15:11:05 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

void	init_struct_exec(t_pipex_b *pipex, t_commands *cmds, char **env)
{
	pipex->cmd_count = ft_lstlen(cmds);
	pipex->outfile = -1;
	pipex->path = NULL;
	pipex->directories = NULL;
	pipex->outfile_error = -1;
	pipex->infile_error = -1;
	pipex->pathname_cmd = NULL;
	pipex->cmd = NULL;
	init_struct_exec_malloc(pipex, cmds, env);
}

void	init_struct_exec_malloc(t_pipex_b *pipex, t_commands *cmds, char **env)
{
	int	i;

	i = 0;
	pipex->pid = ft_malloc(pipex->cmd_count * sizeof(pid_t), 0);
	if (!pipex->pid)
		ft_printf("Pipex pid malloc\n");
	pipex->pipefd = ft_malloc(sizeof(int *) * (pipex->cmd_count), 0);
	if (!pipex->pipefd)
		ft_printf("Malloc pipefd\n");
	while (i < pipex->cmd_count)
		pipex->pid[i++] = -1;
	i = 0;
	while (i < pipex->cmd_count)
		pipex->pipefd[i++] = NULL;
	pipex->path = get_env_value("PATH=", env);
	pipex->directories = ft_split(pipex->path, ':');
}

int	ft_lstlen(t_commands *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (0);
	while (cmds->next)
	{
		i++;
		cmds = cmds->next;
	}
	i++;
	return (i);
}

char	*get_env_value(char *value, char **env)
{
	size_t	len_value;
	size_t	i;

	len_value = ft_strlen(value);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], value, len_value) == 0)
			return (ft_strdup(env[i] + len_value));
		i++;
	}
	return (NULL);
}

void	get_pathname(char **cmd, t_pipex_b *pipex)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	temp = ft_strjoin("/", cmd[0]);
	if (!pipex->directories)
		return ;
	while (pipex->directories[i])
	{
		path = ft_strjoin(pipex->directories[i], temp);
		if (access(path, X_OK) == 0)
		{
			pipex->pathname_cmd = ft_strdup(path);
			break ;
		}
		path = NULL;
		i++;
	}
	if (!path)
		pipex->pathname_cmd = NULL;
}
