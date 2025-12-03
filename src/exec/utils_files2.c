/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:09 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/02 16:13:17 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

int	ft_init_files(t_commands *cmds, t_pipex_b *pipex, t_env *env)
{
	t_redirect	*current;

	current = cmds->redirect;
	while (current)
	{
		if (current->type == FILE_HEREDOC || current->type == FILE_REDIRECT_IN)
		{
			if (ft_init_infiles(current, pipex, env))
				return (1);
		}
		else if (current->type == FILE_REDIRECT_APPEND
			|| current->type == FILE_REDIRECT_OUT)
		{
			if (ft_init_outfiles(current, pipex))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_init_infiles(t_redirect *current, t_pipex_b *pipex, t_env *env)
{
	int			fd;
	t_redirect	*next_in;

	next_in = current->next;
	while (next_in && next_in->type != FILE_HEREDOC
		&& next_in->type != FILE_REDIRECT_IN)
		next_in = next_in->next;
	if (current->type == FILE_HEREDOC)
		fd = get_heredoc(current->word_eof, env);
	else if (current->type == FILE_REDIRECT_IN)
	{
		if (access(current->filename, F_OK) != 0)
			return (error_infile(current->filename, pipex));
		fd = open(current->filename, O_RDONLY);
		if (fd < 0)
			return (error_infile(current->filename, pipex));
	}
	if (next_in)
		close(fd);
	else
	{
		pipex->infile = fd;
		pipex->infile_error = 0;
	}
	return (0);
}

int	error_infile(char *filename, t_pipex_b *pipex)
{
	perror(filename);
	pipex->infile_error = -1;
	return (1);
}

int	ft_init_outfiles(t_redirect *current, t_pipex_b *pipex)
{
	int			fd;
	t_redirect	*next_out;

	next_out = current->next;
	while (next_out && next_out->type != FILE_REDIRECT_OUT
		&& next_out->type != FILE_REDIRECT_APPEND)
		next_out = next_out->next;
	if (current->type == FILE_REDIRECT_OUT)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == FILE_REDIRECT_APPEND)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(current->filename);
		pipex->outfile_error = -1;
		return (1);
	}
	if (next_out)
		close(fd);
	else
	{
		pipex->outfile = fd;
		pipex->outfile_error = 0;
	}
	return (0);
}
