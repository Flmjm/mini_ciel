/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:31:15 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/27 18:59:30 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"
#include "../../include/lib_parse.h"

void	exec_builtin_with_redir(t_pipex_b *pipex, t_commands *cmds,
			t_env *env, int i)
{
	int	saved_stdin;
	int	saved_stdout;
	int	index;

	index = pipex->cmd_index - 1;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (pipex->outfile_error == 0)
		ft_dup2_and_close(pipex->outfile, STDOUT_FILENO);
	else if (index < pipex->cmd_count - 1)
		ft_dup2_and_close(pipex->pipefd[index][1], STDOUT_FILENO);
	if (pipex->infile_error == 0)
		ft_dup2_and_close(pipex->infile, STDIN_FILENO);
	else if (index > 0)
		ft_dup2_and_close(pipex->pipefd[index - 1][0], STDIN_FILENO);
	if (pipex->outfile_error == -1 || pipex->infile_error == -1)
	{
		close_saved_std(saved_stdin, saved_stdout);
		env->exitcode->last_cmd = 1;
		return ;
	}
	exec_builtin(pipex, cmds, env, env->exitcode);
	close_saved_std(saved_stdin, saved_stdout);
}

void	close_saved_std(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
		ft_dup2_and_close(saved_stdin, STDIN_FILENO);
	if (saved_stdout != -1)
		ft_dup2_and_close(saved_stdout, STDOUT_FILENO);
}

void	exec_builtin(t_pipex_b *pipex, t_commands *cmds,
			t_env *env, t_exitcode *exit_code)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if ((ft_strlen(cmds->argv[0]) == 4)
		&& (ft_strncmp("exit", cmds->argv[0], 4) == 0))
		exit_code->last_cmd = ft_exit(env, cmds->argv, 0);
	else if ((ft_strlen(cmds->argv[0]) == 3)
		&& (ft_strncmp("env", cmds->argv[0], 3) == 0))
		exit_code->last_cmd = env_built_in(env);
	else if ((ft_strlen(cmds->argv[0]) == 2)
		&& (ft_strncmp("cd", cmds->argv[0], 2) == 0))
		exit_code->last_cmd = cd_main(argc_of_argv(cmds->argv),
				cmds->argv, env);
	else if ((ft_strlen(cmds->argv[0]) == 4)
		&& (ft_strncmp("echo", cmds->argv[0], 4) == 0))
		exit_code->last_cmd = ft_echo(cmds->argv);
	else if ((ft_strlen(cmds->argv[0]) == 3)
		&& (ft_strncmp("pwd", cmds->argv[0], 3) == 0))
		exit_code->last_cmd = ft_pwd(env);
	else if ((ft_strlen(cmds->argv[0]) == 6)
		&& (ft_strncmp("export", cmds->argv[0], 6) == 0))
		exit_code->last_cmd = ft_export(env, cmds);
	else if ((ft_strlen(cmds->argv[0]) == 5)
		&& (ft_strncmp("unset", cmds->argv[0], 5) == 0))
		exit_code->last_cmd = ft_unset(env, cmds);
}

int	is_builtin(char *cmd)
{
	if ((ft_strlen(cmd) == 4) && (ft_strncmp("exit", cmd, 4) == 0))
		return (1);
	if ((ft_strlen(cmd) == 3) && (ft_strncmp("env", cmd, 3) == 0))
		return (1);
	if ((ft_strlen(cmd) == 2) && (ft_strncmp("cd", cmd, 2) == 0))
		return (1);
	if ((ft_strlen(cmd) == 4) && (ft_strncmp("echo", cmd, 4) == 0))
		return (1);
	if ((ft_strlen(cmd) == 3) && (ft_strncmp("pwd", cmd, 3) == 0))
		return (1);
	if ((ft_strlen(cmd) == 6) && (ft_strncmp("export", cmd, 6) == 0))
		return (1);
	if ((ft_strlen(cmd) == 5) && (ft_strncmp("unset", cmd, 5) == 0))
		return (1);
	return (0);
}

void	exec_builtin_pipe_with_redir(t_pipex_b *pipex, t_commands *cmds,
		t_env *env, int i)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipex->pid[i] = fork();
	env->exitcode->last_cmd = 0;
	if (pipex->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cmd_process(pipex, i, cmds, env);
	}
	if (i > 0)
	{
		close(pipex->pipefd[i - 1][0]);
		close(pipex->pipefd[i - 1][1]);
	}
}
