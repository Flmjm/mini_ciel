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
	{
		if (pipex->outfile_error == 0)
			ft_dup2_and_close(pipex->outfile, STDOUT_FILENO);
		execve(pipex->pathname_cmd, pipex->cmd, env);}
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
	if (cmds->outfiles)
		ft_dup_last_outfile(cmds, pipex);
}

void	ft_dup_last_outfile(t_commands *cmds, t_pipex_b *pipex)
{
	t_commands 	*current;
	char		*last_outfile;

	current = cmds;
	while (current->outfiles && current->outfiles->next)
		current->outfiles = current->outfiles->next;
	last_outfile = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), current->outfiles->outfile);
	if (access(last_outfile, F_OK) == 0)
	{
		if (current->outfiles->type == TOKEN_REDIRECT_OUT)
			pipex->outfile = open(current->outfiles->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->outfiles->type == TOKEN_REDIRECT_APPEND)
			pipex->outfile = open(current->outfiles->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile > 0)
			pipex->outfile_error = 0;
		else
			pipex->outfile_error = -1;
	}
	else
		pipex->outfile_error = -1;
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
