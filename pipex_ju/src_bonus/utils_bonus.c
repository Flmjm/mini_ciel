/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/12 16:20:10 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_struct(t_pipex_b *pipex, char **env)
{
	int	i;

	i = 0;
	pipex->outfile = -1;
	pipex->path = NULL;
	pipex->directories = NULL;
	pipex->outfile_error = 1;
	pipex->pathname_cmd = NULL;
	pipex->cmd = NULL;
	pipex->pid = malloc(pipex->cmd_count * sizeof(pid_t));
	if (!pipex->pid)
		exit_with_message_and_free("Malloc pids", pipex, 1);
	pipex->pipefd = malloc(sizeof(int *) * (pipex->cmd_count));
	if (!pipex->pipefd)
		exit_with_message_and_free("Malloc pipefd", pipex, 1);
	while (i < pipex->cmd_count)
		pipex->pipefd[i++] = NULL;
	pipex->path = get_env_value("PATH=", env);
	if (!pipex->path)
		exit_with_message_and_free("Unable to get PATH", pipex, 1);
	pipex->directories = ft_split(pipex->path, ':');
	if (!pipex->directories)
		exit_with_message_and_free("Split directories", pipex, 1);
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
		free(path);
		path = NULL;
		i++;
	}
	if (!path)
		pipex->pathname_cmd = NULL;
	if (path)
		free(path);
	free(temp);
}

void	init_outfile(t_pipex_b *pipex)
{
	if (access(pipex->path_outfile, F_OK) < 0)
	{
		pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (pipex->outfile < 0)
			perror(pipex->path_outfile);
		else
			pipex->outfile_error = 0;
	}
	else
	{
		if (access(pipex->path_outfile, W_OK) < 0)
			perror(pipex->path_outfile);
		else
		{
			pipex->outfile = open(pipex->path_outfile, O_WRONLY | O_TRUNC);
			pipex->outfile_error = 0;
		}
	}
}

int	init_infile(t_pipex_b *pipex, char **av)
{
	if (access(av[1], F_OK) == 0 && access(av[1], R_OK) < 0)
	{
		init_outfile(pipex);
		free_struct(pipex);
		return (0);
	}
	else if (access(av[1], F_OK) == 0)
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile == -1)
			perror(av[1]);
	}
	else if (access(av[1], F_OK) < 0)
		pipex->infile = open("/dev/null", O_RDONLY);
	return (1);
}
