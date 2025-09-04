/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/08 16:15:30 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	if (index == 0)
	{
		if (pipex->infile > 0)
			ft_dup2_and_close(pipex->infile, 0);
	}
	else
		ft_dup2_and_close(pipex->pipefd[index - 1][0], 0);
	if (index == pipex->cmd_count - 1)
	{
		if (!pipex->pathname_cmd)
			ft_printf("%s : Command not found\n", pipex->cmd[0]);
		if (pipex->outfile_error == 0)
			ft_dup2_and_close(pipex->outfile, 1);
		else
			exit_with_message_and_free(NULL, pipex, 1);
	}
	else
		ft_dup2_and_close(pipex->pipefd[index][1], 1);
	close_fd(pipex);
	if (pipex->pathname_cmd)
		execve(pipex->pathname_cmd, pipex->cmd, env);
	else if (!pipex->pathname_cmd && index == pipex->cmd_count - 1)
		exit_with_message_and_free(NULL, pipex, 127);
	else
		exit_with_message_and_free(NULL, pipex, 127);
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

void	init_cmd(t_pipex_b *pipex, char *av)
{
	pipex->cmd = NULL;
	pipex->cmd = ft_split(av, ' ');
	if (!pipex->cmd)
		exit_with_message_and_free("Split cmd", pipex, 1);
	get_pathname(pipex->cmd, pipex);
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
