/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:42 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/11 17:06:42 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

int cd_dir(char **cmd, char **env, t_env *envpwd, char *pathname, char *tmp_cwd)
{
	char *cwd;
	
	pathname = get_pathname_dir(cmd[1]);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	if (ft_strncmp(pathname, cwd, ft_strlen(pathname)) == 0)
		return(1);
	tmp_cwd = ft_malloc(sizeof(char) * (ft_strlen(cwd) + 1), 0);
	ft_strlcpy(tmp_cwd, cwd, ft_strlen(cwd) + 1);
	if (chdir(pathname) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	else
		return (update_cwd(envpwd, tmp_cwd, pathname));
}

int	ft_cd(char **cmd, char **env, t_env *envpwd)
{
	char *pathname;
	char *tmp_cwd;

	pathname = NULL;
	tmp_cwd = NULL;
	//printf("\\DEBUT\\\n oldpwd: %s\npwd: %s\n", envpwd->oldpwd, envpwd->pwd);
	if (argc_of_argv(cmd) > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0'))
		return(cd_home(envpwd, pathname, env));
	if (cmd[0] && cmd[1][0] == '-' && cmd[1][1] == '\0')
		return(cd_oldpwd(cmd, envpwd, tmp_cwd));
	return(cd_dir(cmd, env, envpwd, pathname, tmp_cwd));
}

int	update_cwd(t_env *envpwd, char *s1_oldpwd, char *s2_pwd)
{
	envpwd->oldpwd = s1_oldpwd;
	envpwd->pwd = s2_pwd;
	//printf("\\APRES FCT\\\n oldpwd: %s\npwd: %s\n", envpwd->oldpwd,
		//envpwd->pwd);
	return (chdir(s2_pwd));
}

int cd_main(int ac, char **av, t_env *envpwd)
{
	// t_env	*envpwd;
	char *pathname;
	char *cwd;

	// envpwd = ft_malloc(sizeof(t_env), 0);
	// envpwd->pwd = "OLDPWD=""/home/";
	if (!envpwd->pwd)
	{
		pathname = get_env_value("HOME=", envpwd->local_env);
		if (!pathname)
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		else
			envpwd->oldpwd = pathname;
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return(1);
		envpwd->pwd = ft_malloc(ft_strlen(cwd) + 1, 0);
		ft_strlcpy(envpwd->pwd, cwd, ft_strlen(cwd) + 1);
		free(cwd);
	}
	if (ac >= 1)
		ft_cd(av, envpwd->local_env, envpwd);
	return(0);
}
