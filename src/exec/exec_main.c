/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/09 21:49:16 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"
#include "../../include/lib_parse.h"


int	exec_main(t_commands *cmds, t_env *env, t_exitcode *exit_code)
{
	t_pipex_b	*pipex;
	int			ret;

	ret = 0;
		pipex = ft_malloc(sizeof(t_pipex_b), 0);
		if (!pipex)
			ft_printf("Malloc pipex\n");
		init_struct_exec(pipex, cmds, env->local_env);
		create_pipe(pipex);
		ft_pipex(pipex, cmds, env, exit_code);
	return (ret);
}

int	argc_of_argv(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void exec_not_builtin(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code, int i)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pipex->pid[i] == 0 && pipex->pathname_cmd)
		cmd_process(pipex, env->local_env, i);
	else if (pipex->pid[i] == 0 && !pipex->pathname_cmd)
	{
		ft_printf("%s : Command not found\n", pipex->cmd[0]);
		ft_exit(env, 127);
	}
	if (i > 0)
	{
		close(pipex->pipefd[i - 1][0]);
		close(pipex->pipefd[i - 1][1]);
	}
}

void	ft_pipex(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code)
{
	int	i;

	i = 0;
	pipex->cmd_index = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_index++;
		init_cmd(pipex, cmds);
		if (is_builtin(cmds->argv[0]))
		{
			exec_builtin_with_redir(pipex, cmds, env, exit_code);
			if (i > 0)
			{
				close(pipex->pipefd[i - 1][0]);
				close(pipex->pipefd[i - 1][1]);
			}
		}
		else
			exec_not_builtin(pipex, cmds, env, exit_code, i);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
	// if (pipex->pid[pipex->cmd_count - 1] > 0)
	// 	exit_code->last_cmd = ft_waitpid(pipex, env, exit_code);
	// else
		ft_waitpid(pipex, env, exit_code);
}

void	ft_waitpid(t_pipex_b *pipex, t_env *env, t_exitcode *exit_code)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	status = 0;
	last_status = 0;
	while (i < pipex->cmd_count)
	{
		if (pipex->pid[i] > 0)
		{
			status = 0;
			waitpid(pipex->pid[i], &status, 0);
			if (i == pipex->cmd_count - 1)
				last_status = status;
		}
		i++;
	}
	if (WIFEXITED(last_status))
		exit_code->last_cmd = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
	{
		exit_code->last_cmd = 128 + WTERMSIG(last_status);
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
	}
	env->signal->sa_handler = &manage_ctrlc;
	sigemptyset(&env->signal->sa_mask);
	env->signal->sa_flags = SA_RESTART;
	sigaction(SIGINT, env->signal, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	create_pipe(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipefd[i] = ft_malloc(sizeof(int) * 2, 0);
		if (!pipex->pipefd[i])
			ft_printf("Malloc pipefd");
		if (pipe(pipex->pipefd[i]) == -1)
			ft_printf("Pipe");
		i++;
	}
	pipex->pipefd[i] = NULL;
}
