/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/17 01:01:12 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_struct(t_pipex_b *pipex)
{
	if (pipex)
	{
		if (pipex->directories)
			free_tab(pipex->directories);
		if (pipex->path)
			ft_free(pipex->path);
		if (pipex->pathname_cmd)
			ft_free(pipex->pathname_cmd);
		if (pipex->cmd)
			free_tab(pipex->cmd);
		if (pipex->pid)
			ft_free(pipex->pid);
		if (pipex->pipefd)
			free_pipe(pipex);
		free(pipex);
	}
}

void	free_pipe(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		free(pipex->pipefd[i]);
		i++;
	}
	free(pipex->pipefd);
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
