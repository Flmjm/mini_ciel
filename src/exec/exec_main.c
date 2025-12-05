/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/12/05 18:46:36 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"
#include "../../include/lib_parse.h"

int	exec_main(t_commands *cmds, t_env *env, t_exitcode *exit_code)
{
	t_pipex_b	*pipex;

	pipex = ft_malloc(sizeof(t_pipex_b), 0);
	env->exitcode->here_doc_error = 0;
	if (!pipex)
		ft_printf("Malloc pipex\n");
	init_struct_exec(pipex, cmds, env->global);
	create_pipe(pipex);
	ft_pipex(pipex, cmds, env);
	return (0);
}

int	argc_of_argv(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	exec_not_builtin(t_pipex_b *pipex, t_commands *cmds, t_env *env, int i)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipex->pid[i] = fork();
	env->exitcode->last_cmd = 0;
	if (pipex->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (pipex->pid[i] == 0 && cmds->argv[0] && pipex->pathname_cmd)
		cmd_process(pipex, i, cmds, env);
	else if (pipex->pid[i] == 0 && cmds->argv[0] && !pipex->pathname_cmd)
	{
		ft_printf("%s : Command not found\n", pipex->cmd[0]);
		ft_exit(env, NULL, 127);
	}
	if (i > 0)
	{
		close(pipex->pipefd[i - 1][0]);
		close(pipex->pipefd[i - 1][1]);
	}
}

void	ft_pipex(t_pipex_b *pipex, t_commands *cmds, t_env *env)
{
	int	i;

	i = 0;
	pipex->cmd_index = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_index++;
		if (init_cmd(pipex, cmds, env))
			env->exitcode->last_cmd = 1;
		if (env->exitcode->here_doc_error == -1)
			return ;
		else if (is_builtin(cmds->argv[0]) && pipex->cmd_count == 1)
			exec_builtin_with_redir(pipex, cmds, env, i);
		else if (is_builtin(cmds->argv[0]))
			exec_builtin_pipe_with_redir(pipex, cmds, env, i);
		else
			exec_not_builtin(pipex, cmds, env, i);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
	ft_waitpid(pipex, env, env->exitcode);
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
