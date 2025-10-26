/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/09 17:41:38 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex_b	*pipex;
	int			ret;

	ret = 0;
	if (argc < 5)
		exit_with_message("Incorrect number of arguments", 1);
	if (access(argv[1], F_OK) < 0)
		perror(argv[1]);
	pipex = malloc(sizeof(t_pipex_b));
	if (!pipex)
		exit_with_message("Pipex malloc", 1);
	pipex->path_outfile = argv[argc - 1];
	pipex->cmd_count = argc - 3;
	init_struct(pipex, env);
	if (init_infile(pipex, argv) == 0)
		return (0);
	create_pipe(pipex);
	ft_pipex(pipex, argv, env);
	ret = ft_waitpid(pipex);
	if (pipex->outfile_error == 1)
		exit_with_message_and_free(NULL, pipex, 1);
	free_struct(pipex);
	return (ret);
}

void	ft_pipex(t_pipex_b *pipex, char **argv, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		init_cmd(pipex, argv[i + 2]);
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			exit_with_message_and_free("pid", pipex, 1);
		if (pipex->pid[i] == 0 && pipex->pathname_cmd)
			cmd_process(pipex, env, i);
		else if (pipex->pid[i] == 0 && !pipex->pathname_cmd)
		{
			ft_printf("%s : Command not found\n", pipex->cmd[0]);
			exit_with_message_and_free(NULL, pipex, 127);
		}
		if (pipex->pipefd[i][1] != -1)
			close(pipex->pipefd[i][1]);
		if (i > 0 && pipex->pipefd[i - 1][0] != -1)
			close(pipex->pipefd[i - 1][0]);
		free_tab(pipex->cmd);
		free(pipex->pathname_cmd);
		i++;
	}
	last_cmd(pipex, argv, env, i);
}

void	last_cmd(t_pipex_b *pipex, char **argv, char **env, int i)
{
	init_cmd(pipex, argv[i + 2]);
	init_outfile(pipex);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		exit_with_message_and_free("pid", pipex, 1);
	if (pipex->pid[i] == 0)
		cmd_process(pipex, env, i);
	if (pipex->pipefd[i - 1][0] != -1)
		close(pipex->pipefd[i - 1][0]);
}

int	ft_waitpid(t_pipex_b *pipex)
{
	int	i;
	int	ret;
	int	status;

	i = 0;
	ret = 0;
	status = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i], &status, 0);
		ret = (status >> 8) & 0xFF;
		i++;
	}
	return (ret);
}

void	create_pipe(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipefd[i])
			exit_with_message_and_free("Malloc pipefd", pipex, 1);
		if (pipe(pipex->pipefd[i]) == -1)
			exit_with_message_and_free("Pipe", pipex, 1);
		i++;
	}
	pipex->pipefd[i] = NULL;
}
