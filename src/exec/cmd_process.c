/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/17 05:22:29 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	if (pipex->outfile_error == -1 || pipex->infile_error == -1)
		exit(1);
	if (pipex->outfile_error == 0)
		dup2(pipex->outfile, STDOUT_FILENO);
	else if (index < pipex->cmd_count - 1)
		dup2(pipex->pipefd[index][1], STDOUT_FILENO);
	if (pipex->infile_error == 0)
		dup2(pipex->infile, STDIN_FILENO);
	else if (index > 0)
		dup2(pipex->pipefd[index - 1][0], STDIN_FILENO);
	close_fd(pipex);
	if (pipex->outfile_error == 0)
		close(pipex->outfile);
	if (pipex->infile_error == 0)
		close(pipex->infile);
	if (pipex->cmd_count)
		execve(pipex->pathname_cmd, pipex->cmd, env);
	perror("execve");
	exit(127);
}

int	init_cmd(t_pipex_b *pipex, t_commands *cmds)
{
	pipex->cmd = cmds->argv;
	pipex->outfile_error = 1;
	pipex->infile_error = 1;
	if (is_relative_or_absolute_path(cmds->argv[0]) == 0)
		get_pathname(pipex->cmd, pipex);
	else
		pipex->pathname_cmd = cmds->argv[0];
	if (cmds->redirect)
		return (ft_init_files(cmds, pipex));
	return (0);
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
