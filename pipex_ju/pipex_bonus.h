/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/07 15:16:42 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char	*path_outfile;
	int		cmd_count;
	pid_t	*pid;
}			t_pipex_b;

///////////////////////////// utils.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
void		get_pathname(char **cmd, t_pipex_b *pipex);
void		init_struct(t_pipex_b *pipex, char **env);
void		init_outfile(t_pipex_b *pipex);
int			init_infile(t_pipex_b *pipex, char **av);

///////////////////////////// free_errors.c ///////////////////////////////////
void		exit_with_message(char *str, int n);
void		exit_with_message_and_free(char *str, t_pipex_b *pipex, int n);
void		free_tab(char **tab);
void		free_struct(t_pipex_b *pipex);
void		free_pipe(t_pipex_b *pipex);

///////////////////////////// pipex.c ///////////////////////////////////
void		cmd_process(t_pipex_b *pipex, char **env, int index);
void		close_fd(t_pipex_b *pipex);
void		ft_dup2_and_close(int fd, int n);
void		init_cmd(t_pipex_b *pipex, char *av);
void		ft_free(void *ptr);

///////////////////////////// main.c ////////////////////////////////////
void		ft_pipex(t_pipex_b *pipex, char **argv, char **env);
void		last_cmd(t_pipex_b *pipex, char **argv, char **env, int i);
int			ft_waitpid(t_pipex_b *pipex);
void		create_pipe(t_pipex_b *pipex);

#endif