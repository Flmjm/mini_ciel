/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/28 15:54:34 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// # include "libft/ft_printf/ft_printf.h"
// # include "libft/libft.h"
# include "../lib_parse.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
# define PATH_MAX 100
# endif

typedef struct s_pipex_b
{
	int		infile;
	int		outfile;
	int		nullfile;
	char	**cmd;
	char	**directories;
	char	*path;
	char	*pathname_cmd;
	int		**pipefd;
	int		outfile_error;
	int		infile_error;
	char	*path_outfile;
	int		cmd_count;
	int		cmd_index;
	pid_t	*pid;
}			t_pipex_b;

///////////////////////////// utils.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
void		get_pathname(char **cmd, t_pipex_b *pipex);
void		init_struct_exec(t_pipex_b *pipex, t_commands *cmds, char **env);
// void		init_outfile(t_pipex_b *pipex);
// int			init_infile(t_pipex_b *pipex, char **av);

///////////////////////////// free_errors.c ///////////////////////////////////
// void		exit_with_message(char *str, int n);
// void		exit_with_message_and_free(char *str, t_pipex_b *pipex, int n);
void		free_tab(char **tab);
void		free_struct(t_pipex_b *pipex);
void		free_pipe(t_pipex_b *pipex);

///////////////////////////// pipex.c ///////////////////////////////////
void		cmd_process(t_pipex_b *pipex, char **env, int index);
void		close_fd(t_pipex_b *pipex);
void		ft_dup2_and_close(int fd, int n);
void		init_cmd(t_pipex_b *pipex, t_commands *cmds);
void		ft_free(void *ptr);
int			is_relative_or_absolute_path(char *str);
void	ft_dup_last_outfile(t_commands *cmds, t_pipex_b *pipex);
void	ft_dup_last_infiles(t_commands *cmds, t_pipex_b *pipex);

///////////////////////////// main.c ////////////////////////////////////
void		ft_pipex(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code);
void		last_cmd(t_pipex_b *pipex, t_commands *cmds, char **env, int i);
int			ft_waitpid(t_pipex_b *pipex);
void		create_pipe(t_pipex_b *pipex);
int			ft_lstlen(struct t_commands *cmds);
int			exec_main(t_commands *cmds, t_env *env, t_exitcode *exitcode);
void		ft_wait_last_cmd(t_pipex_b *pipex, int i_cmd, t_exitcode *exit_code);
int			argc_of_argv(char **cmds);
char		*prompt_sentence(t_env *env);


// ----> built_ins
int			cd_main(int ac, char **av, t_env *envpwd);
int		    ft_echo(char **cmd);
int			ft_pwd();

#endif
