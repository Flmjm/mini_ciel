/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/28 16:34:51 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cmd_process(t_pipex_b *pipex, char **env, int index)
{
	if (pipex->outfile_error == 0)
		ft_dup2_and_close(pipex->outfile, STDOUT_FILENO);
	else if (index < pipex->cmd_count - 1)
		ft_dup2_and_close(pipex->pipefd[index][1], STDOUT_FILENO);
	if (pipex->infile_error == 0)
		ft_dup2_and_close(pipex->infile, STDIN_FILENO);
	else if (index > 0)
		ft_dup2_and_close(pipex->pipefd[index - 1][0], STDIN_FILENO);
	close_fd(pipex);
	if (pipex->cmd_count)
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
	if (cmds->outfiles)
		ft_dup_last_outfile(cmds, pipex);
	if (cmds->infiles)
		ft_dup_last_infiles(cmds, pipex);
}

void	ft_dup_last_outfile(t_commands *cmds, t_pipex_b *pipex)
{
	t_commands 	*current;
	char		*last_outfile;

	current = cmds;
	while (current->outfiles && current->outfiles->next)
	{
		open(current->outfiles->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);	
		current->outfiles = current->outfiles->next;
	}
	last_outfile = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), current->outfiles->outfile);

	if (current->outfiles->type == TOKEN_REDIRECT_OUT)
		pipex->outfile = open(current->outfiles->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->outfiles->type == TOKEN_REDIRECT_APPEND)
		pipex->outfile = open(current->outfiles->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile > 0)
		pipex->outfile_error = 0;
	else
		pipex->outfile_error = -1;

}

void	ft_dup_last_infiles(t_commands *cmds, t_pipex_b *pipex)
{
	t_commands 	*current;
	char		*last_infile;

	current = cmds;
	while (current->infiles && current->infiles->next)
		current->infiles = current->infiles->next;
	last_infile = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), current->infiles->infile);
	if (access(last_infile, F_OK) == 0)
	{
		if (current->infiles->type == TOKEN_REDIRECT_IN)
			pipex->infile = open(current->infiles->infile, O_RDONLY);
		else if (current->infiles->type == TOKEN_HEREDOC)
			pipex->infile = open(current->infiles->infile, O_RDONLY);
		else if (current->infiles->type == TOKEN_HERESTRING)
			pipex->infile = open(current->infiles->infile, O_RDONLY);
		if (pipex->infile > 0)
			pipex->infile_error = 0;
		else
			pipex->infile_error = -1;
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
