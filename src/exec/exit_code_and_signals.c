/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_and_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:56:49 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/17 01:00:22 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

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
	get_exit_code(last_status, exit_code);
	env->signal->sa_handler = &manage_ctrlc;
	sigemptyset(&env->signal->sa_mask);
	env->signal->sa_flags = SA_RESTART;
	sigaction(SIGINT, env->signal, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	get_exit_code(int last_status, t_exitcode *exit_code)
{
	if (WIFEXITED(last_status) && !exit_code->last_cmd)
		exit_code->last_cmd = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
	{
		exit_code->last_cmd = 128 + WTERMSIG(last_status);
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
	}
}
