/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/20 01:51:09 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct_exec(t_pipex_b *pipex, t_commands *cmds, char **env)
{
	int	i;

	i = 0;
	pipex->cmd_count = ft_lstlen(cmds);
	pipex->outfile = -1;
	pipex->path = NULL;
	pipex->directories = NULL;
	pipex->outfile_error = -1;
	pipex->infile_error = -1;
	pipex->pathname_cmd = NULL;
	pipex->cmd = NULL;
	pipex->pid = ft_malloc(pipex->cmd_count * sizeof(pid_t), 0);
	if (!pipex->pid)
		printf("pipex pid malloc\n");
	pipex->pipefd = ft_malloc(sizeof(int *) * (pipex->cmd_count), 0);
	if (!pipex->pipefd)
		printf("Malloc pipefd");
	while (i < pipex->cmd_count)
		pipex->pipefd[i++] = NULL;
	pipex->path = get_env_value("PATH=", env);
	if (!pipex->path)
		printf("Unable to get PATH");
	pipex->directories = ft_split(pipex->path, ':');
	if (!pipex->directories)
		printf("Split directories");
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

// void	init_outfile(t_pipex_b *pipex)
// {
// 	if (access(pipex->path_outfile, F_OK) < 0)
// 	{
// 		pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_CREAT | O_TRUNC,
// 				0644);
// 		if (pipex->outfile < 0)
// 			perror(pipex->path_outfile);
// 		else
// 			pipex->outfile_error = 0;
// 	}
// 	else
// 	{
// 		if (access(pipex->path_outfile, W_OK) < 0)
// 			perror(pipex->path_outfile);
// 		else
// 		{
// 			pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_TRUNC);
// 			pipex->outfile_error = 0;
// 		}
// 	}
// }

// int	init_infile(t_pipex_b *pipex, char **av)
// {
// 	if (access(av[1], F_OK) == 0 && access(av[1], R_OK) < 0)
// 	{
// 		init_outfile(pipex);
// 		free_struct(pipex);
// 		return (0);
// 	}
// 	else if (access(av[1], F_OK) == 0)
// 	{
// 		pipex->infile = open(av[1], O_RDONLY);
// 		if (pipex->infile == -1)
// 			perror(av[1]);
// 	}
// 	else if (access(av[1], F_OK) < 0)
// 		pipex->infile = open("/dev/null", O_RDONLY);
// 	return (1);
// }
