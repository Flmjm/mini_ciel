/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:04:34 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/09/23 14:42:31 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../pipex_ju/pipex_bonus.h"
#include "../pipex_ju/ft_printf/ft_printf.h"
#include "../pipex_ju/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/param.h>

typedef	struct s_env
{
	char **export;	//varibale d'en exporter
	char **local_env; // varibale d'env locale + exporter
}						t_env;

typedef	struct s_tmp_env
{
    char *oldpwd;
    char *pwd;	
}				t_tmp_env;


// ft_cd.c
char	*get_env_value(char *value, char **env);
int    ft_cd(char **cmd, char **env, t_tmp_env *envpwd); //a modifier pour ta struct env 
//ft_echo.c
int check_option_n(char *str);
void    ft_echo(char **cmd); //(char **cmd, int fd)
//ft_pwd.c
int ft_pwd();
int	update_cwd(t_tmp_env *envpwd, char *s1_oldpwd, char *s2_pwd);
int	count_args(char **cmd);
int cd_oldpwd(char **cmd, t_tmp_env *envpwd, char *tmp_cwd);
int	cd_home(t_tmp_env *envpwd, char *pathname, char **env);

#endif
