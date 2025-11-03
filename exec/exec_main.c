/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/29 11:41:57 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../lib_parse.h"

int	exec_main(t_commands *cmds, t_env *env, t_exitcode *exit_code)
{
	t_pipex_b	*pipex;
	int			ret;

	ret = 0;
		pipex = ft_malloc(sizeof(t_pipex_b), 0);
		if (!pipex)
			printf("malloc pipex\n");
		init_struct_exec(pipex, cmds, env->local_env);
		create_pipe(pipex);
		ft_pipex(pipex, cmds, env, exit_code);
	return (ret);
}

void	clean_quote_in_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\'')
			argv[i] = clean_simple_quote(argv[i]);
		else if (argv[i][0] == '"')
			argv[i] = clean_double_quote(argv[i]);
		i++;
	}
}

char	*clean_simple_quote(char *str) // faut rajouter le cas <<''>>
{
	char *temp;
	int	i;

	i = 1;
	temp = ft_malloc(sizeof (char) * (ft_strlen(str) - 2), 0);
	while (str[i] != '\'')
	{
		temp[i - 1] = str[i];
		i++;
	}
	return (temp);
}

char	*clean_double_quote(char *str) // faut rajouter le cas <<"">>
{
	char *temp;
	int	i;

	i = 1;
	temp = ft_malloc(sizeof (char) * (ft_strlen(str) - 2), 0);
	while (str[i] != '"')
	{
		temp[i - 1] = str[i];
		i++;
	}
	return (temp);
}

int	argc_of_argv(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	ft_pipex(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code)
{
	int	i;

	i = 0;
	pipex->cmd_index = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_index++;
		if ((ft_strlen(cmds->argv[0]) == 4) && (ft_strncmp("exit", cmds->argv[0], 4) == 0))
			ft_exit(env, 0);
		else if ((ft_strlen(cmds->argv[0]) == 3) && (ft_strncmp("env", cmds->argv[0], 3) == 0))
			env_built_in(env);
		else if ((ft_strlen(cmds->argv[0]) == 2) && (ft_strncmp("cd", cmds->argv[0], 2) == 0))
			cd_main(argc_of_argv(cmds->argv), cmds->argv, env);
		else if ((ft_strlen(cmds->argv[0]) == 4) && (ft_strncmp("echo", cmds->argv[0], 4) == 0))
			ft_echo(cmds->argv);
		else if ((ft_strlen(cmds->argv[0]) == 3) && (ft_strncmp("pwd", cmds->argv[0], 3) == 0))
			ft_pwd();
		else
		{
			init_cmd(pipex, cmds);
			pipex->pid[i] = fork();
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
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
	ft_waitpid(pipex);
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

void	ft_wait_last_cmd(t_pipex_b *pipex, int i_cmd, t_exitcode *exit_code)
{
	int	i;
	int	ret;
	int	status;

	i = i_cmd - 1;
	ret = 0;
	status = 0;
	waitpid(pipex->pid[i], &status, 0);
	if (WIFEXITED(status))
		exit_code->last_cmd = WEXITSTATUS(status);
}

void	create_pipe(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipefd[i] = ft_malloc(sizeof(int) * 2, 0);
		if (!pipex->pipefd[i])
			printf("Malloc pipefd");
		if (pipe(pipex->pipefd[i]) == -1)
			printf("Pipe");
		i++;
	}
	pipex->pipefd[i] = NULL;
}
