/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:42 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/01 23:59:50 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

int	cd_dir(char **cmd, t_env *envpwd, char *pathname, char *tmp_cwd)
{
	char	*cwd;
	int		freeable;

	freeable = 0;
	pathname = get_pathname_dir(cmd[1], envpwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (envpwd->pwd)
			cwd = ft_strdup(envpwd->pwd);
		else
			return (1);
	}
	else
		freeable = 1;
	if (ft_strncmp(pathname, cwd, ft_strlen(pathname)) == 0)
		return (1);
	tmp_cwd = ft_malloc(sizeof(char) * (ft_strlen(cwd) + 1), 0);
	ft_strlcpy(tmp_cwd, cwd, ft_strlen(cwd) + 1);
	if (freeable)
		free(cwd);
	if (chdir(pathname) != 0)
		return (perror_and_return(cmd));
	return (update_cwd(envpwd, tmp_cwd, pathname));
}

int	ft_cd(char **cmd, char **env, t_env *envpwd)
{
	char	*pathname;
	char	*tmp_cwd;

	pathname = NULL;
	tmp_cwd = NULL;
	if (argc_of_argv(cmd) > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (cmd[1] && (ft_strncmp(envpwd->pwd, cmd[1], ft_strlen(cmd[1])) == 0))
		return (0);
	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0'))
		return (cd_home(envpwd, pathname, env, 0));
	if (cmd[0] && cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (cd_oldpwd(cmd, envpwd, tmp_cwd));
	return (cd_dir(cmd, envpwd, pathname, tmp_cwd));
}

int	update_cwd(t_env *envpwd, char *s1_oldpwd, char *s2_pwd)
{
	envpwd->oldpwd = s1_oldpwd;
	envpwd->pwd = s2_pwd;
	update_env_pwd(envpwd, s2_pwd, s1_oldpwd);
	return (chdir(s2_pwd));
}

int	cd_main(int ac, char **av, t_env *envpwd)
{
	char	*pathname;
	char	*cwd;

	if (!envpwd->pwd)
	{
		pathname = get_env_value("HOME=", envpwd->global);
		if (!pathname)
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		else
			envpwd->oldpwd = pathname;
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			envpwd->pwd = ft_malloc(ft_strlen(cwd) + 1, 0);
			ft_strlcpy(envpwd->pwd, cwd, ft_strlen(cwd) + 1);
			free(cwd);
		}
	}
	if (ac >= 1)
		return (ft_cd(av, envpwd->global, envpwd));
	return (0);
}

void	update_env_pwd(t_env *env, char *new_pwd, char *new_oldpwd)
{
	int	i;

	i = 0;
	while (env->global[i])
	{
		if (ft_strncmp("OLDPWD=", env->global[i], 7) == 0)
			env->global[i] = ft_strjoin("OLDPWD=", new_oldpwd);
		else if (ft_strncmp("PWD=", env->global[i], 4) == 0)
			env->global[i] = ft_strjoin("PWD=", new_pwd);
		i++;
	}
}
