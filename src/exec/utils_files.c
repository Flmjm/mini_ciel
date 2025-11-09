/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:09 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/08 15:52:28 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

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

void	ft_dup_outfile(t_commands *cmds, t_pipex_b *pipex)
{
	t_outfiles	*current;
	int			fd;

	current = cmds->outfiles;
	while (current)
	{
		if (current->type == TOKEN_REDIRECT_OUT)
			fd = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == TOKEN_REDIRECT_APPEND)
			fd = open(current->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);	
		if (fd < 0)
		{
			perror(current->outfile);
			pipex->outfile_error = -1;
			return ;
		}
		if (current->next)
			close(fd);
		else
		{
			pipex->outfile = fd;
			pipex->outfile_error = 0;
		}
		current = current->next;
	}
}

void	ft_dup_infiles(t_commands *cmds, t_pipex_b *pipex)
{
	t_infiles	*current;
	int			fd;

	current = cmds->infiles;
	while (current)
	{
		if (current->type == FILE_HEREDOC)
			fd = get_heredoc(current->word_eof);
		else
		{
			if (access(current->infile, F_OK) != 0)
			{
				perror(current->infile);
				pipex->infile_error = -1;
				return ;
			}
			fd = open(current->infile, O_RDONLY);
			if (fd < 0)
			{
				perror(current->infile);
				pipex->infile_error = -1;
				return ;
			}
		}
		if (current->next)
			close(fd);
		else
		{
			pipex->infile = fd;
			pipex->infile_error = 0;
		}
		current = current->next;
	}
}
