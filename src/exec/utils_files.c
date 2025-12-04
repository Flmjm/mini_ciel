/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:51:09 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/04 13:50:54 by mleschev         ###   ########.fr       */
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

int	get_heredoc(char *delimiter, t_env *env)
{
	int		pipefd[2];
	char	*line;
	char	*expanded_line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline(">");
		if (line[0] && ft_strncmp(line, delimiter, ft_strlen(line)) == 0
			&& ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_line(line, env);
		write(pipefd[1], expanded_line, ft_strlen(expanded_line));
		write(pipefd[1], "\n", 1);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

char	*expand_line(char *line, t_env *env)
{
	t_input_info	temp_info;

	if (!line)
		return (NULL);
	temp_info.input = line;
	temp_info.argv = NULL;
	temp_info.nbr_args = 0;
	replace_var_input(&temp_info, env);
	return (temp_info.input);
}
