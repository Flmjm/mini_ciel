/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/20 03:35:11 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	close_fd(pipex);
	if (!pipex->pathname_cmd)
		ft_printf("%s : Command not found\n", pipex->cmd[0]);
	else
		execve(pipex->pathname_cmd, pipex->cmd, env);
}

void	close_fd(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipex->pipefd[i][0] != -1)
		{
			close(pipex->pipefd[i][0]);
			pipex->pipefd[i][0] = -1;
		}
		if (pipex->pipefd[i][1] != -1)
		{
			close(pipex->pipefd[i][1]);
			pipex->pipefd[i][1] = -1;
		}
		i++;
	}
}

void	ft_dup2_and_close(int fd, int n)
{
	dup2(fd, n);
	if (fd != -1)
		close(fd);
}

void	init_cmd(t_pipex_b *pipex, t_commands *cmds)
{
	pipex->cmd = cmds->argv;
	if (is_relative_or_absolute_path(cmds->argv[0]) == 0)
		get_pathname(pipex->cmd, pipex);
	else
		pipex->pathname_cmd = cmds->argv[0];
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	is_relative_or_absolute_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
