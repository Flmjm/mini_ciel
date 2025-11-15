/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/15 23:38:48 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H


# include "lib_parse.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>


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

//cmd_process.c						OK
void		cmd_process(t_pipex_b *pipex, char **env, int index);
int		init_cmd(t_pipex_b *pipex, t_commands *cmds);
int	is_relative_or_absolute_path(char *str);

//exec_builtin.c					OK
void	exec_builtin_with_redir(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code);
void exec_builtin(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code);
int	is_builtin(char *cmd);
void close_saved_std(int saved_stdin, int saved_stdout);

//exec_main.c
int	exec_main(t_commands *cmds, t_env *env, t_exitcode *exit_code);
int	argc_of_argv(char **cmds);
void exec_not_builtin(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code, int i);
void	ft_pipex(t_pipex_b *pipex, t_commands *cmds, t_env *env, t_exitcode *exit_code);
void	create_pipe(t_pipex_b *pipex);

//exit_code_and_signals.c
void	ft_waitpid(t_pipex_b *pipex, t_env *env, t_exitcode *exit_code);
void get_exit_code(int last_status, t_exitcode *exit_code);

//free_errors.c							OK
void	free_tab(char **tab);
void	free_struct(t_pipex_b *pipex);
void	free_pipe(t_pipex_b *pipex);
void	ft_free(void *ptr);

//utils_files.c							
void		close_fd(t_pipex_b *pipex);
void		ft_dup2_and_close(int fd, int n);
int get_heredoc(char *delimiter);

//utils_files2.c							
int	ft_init_files(t_commands *cmds, t_pipex_b *pipex);
int ft_init_infiles(t_redirect *current, t_pipex_b *pipex);
int ft_init_outfiles(t_redirect *current, t_pipex_b *pipex);
int error_infile(char *filename, t_pipex_b *pipex);

//utils.c								OK 
void	init_struct_exec(t_pipex_b *pipex, t_commands *cmds, char **env);
void	init_struct_exec_malloc(t_pipex_b *pipex, t_commands *cmds, char **env);
int	ft_lstlen(t_commands *cmds);
char		*get_env_value(char *value, char **env);
void		get_pathname(char **cmd, t_pipex_b *pipex);



/// BUILT_INS ///
//built_in.c
int			env_built_in(t_env *env); 
char		**ft_env(char **environ, t_env *env);	//init la struct env
void		up_shell_level(char **env); //augmente le niveau du shell dans les variable d'env
char		**add_var(char *new_var, t_env *env);

// unset.c
int    ft_unset(t_env *env, t_commands *cmds);

// export.c
int    ft_export(t_env *env, t_commands *cmds);

//cd_utils.c
char	*get_pathname_dir(char *cmd);
int	cd_home(t_env *envpwd, char *pathname, char **env);
int cd_oldpwd(char **cmd, t_env *envpwd, char *tmp_cwd);

// cd.c  --> 6 fonctions + factoriser 
int cd_dir(char **cmd, char **env, t_env *envpwd, char *pathname, char *tmp_cwd);
int	ft_cd(char **cmd, char **env, t_env *envpwd);
int	update_cwd(t_env *envpwd, char *s1_oldpwd, char *s2_pwd);
int cd_main(int ac, char **av, t_env *envpwd);

//echo.c
int    ft_echo(char **cmd);

//exit.c
int	ft_exit(t_env *env, char **cmds, int nbr_return);
void clear_and_exit(int n);

//pwd.c
int ft_pwd();


#endif
