/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/20 23:49:54 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../lib_parse.h"

int	exec_main(t_commands *cmds, t_env *env)
{
	t_pipex_b	*pipex;
	int			ret;

	ret = 0;
	if ((ft_strlen(cmds->argv[0]) == 4) || (ft_strlen(cmds->argv[0]) == 3)) //built-in
	{
		if ((ft_strlen(cmds->argv[0]) == 4) && (ft_strncmp("exit", cmds->argv[0], 4) == 0))
			ft_exit(env);
		else if ((ft_strlen(cmds->argv[0]) == 3) && (ft_strncmp("env", cmds->argv[0], 3) == 0))
			env_built_in(env);
	}
	else //cmd non built-in
	{
	pipex = ft_malloc(sizeof(t_pipex_b), 0);
	if (!pipex)
		printf("malloc pipex\n");
	init_struct_exec(pipex, cmds, env->local_env);
	create_pipe(pipex);
	ft_pipex(pipex, cmds, env->local_env);
	ret = ft_waitpid(pipex);
	}
	return (ret);
}

void	ft_pipex(t_pipex_b *pipex, t_commands *cmds, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		init_cmd(pipex, cmds);
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			ft_printf("DEBUG : pid %d", pipex->pid);
		if (pipex->pid[i] == 0 && pipex->pathname_cmd)
			cmd_process(pipex, env, i);
		else if (pipex->pid[i] == 0 && !pipex->pathname_cmd)
			ft_printf("%s : Command not found\n", pipex->cmd[0]);
		if (pipex->pipefd[i][1] != -1)
			close(pipex->pipefd[i][1]);
		if (i > 0 && pipex->pipefd[i - 1][0] != -1)
			close(pipex->pipefd[i - 1][0]);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
	last_cmd(pipex, cmds, env, i);
}

void	last_cmd(t_pipex_b *pipex, t_commands *cmds, char **env, int i)
{
	init_cmd(pipex, cmds);
	// init_outfile(pipex);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		printf("aled in lastcmd");
	if (pipex->pid[i] == 0)
		cmd_process(pipex, env, i);
	printf("I:%d\n", i);
	// if (pipex->pipefd[i - 1][0] != -1)
	// 	close(pipex->pipefd[i - 1][0]);
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
		pipex->pipefd[i] = ft_malloc(sizeof(int) * 2, 0);
		printf("DEBUG: pipefd:%p i:%d\n", pipex->pipefd[i], i);
		if (!pipex->pipefd[i])
			printf("Malloc pipefd");
		if (pipe(pipex->pipefd[i]) == -1)
			printf("Pipe");
		i++;
	}
	pipex->pipefd[i] = NULL;
}
