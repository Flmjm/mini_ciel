/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:58:39 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/01 23:59:57 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

char	*get_pathname_dir(char *cmd, t_env *env)
{
	char	*temp;
	char	*path;
	char	*cwd;
	int		freeable;

	freeable = 0;
	path = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (env->pwd)
			cwd = ft_strdup(env->pwd);
		else
			return (NULL);
	}
	else
		freeable = 1;
	temp = ft_strjoin("/", cmd);
	path = ft_strjoin(cwd, temp);
	if (freeable)
		free(cwd);
	return (path);
}

int	cd_home(t_env *envpwd, char *pathname, char **env, int freeable)
{
	char	*old_pwd;
	char	*old_copy;

	pathname = get_env_value("HOME=", env);
	if (!pathname)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		if (envpwd->pwd)
			old_pwd = ft_strdup(envpwd->pwd);
		else
			return (1);
	}
	else
		freeable = 1;
	old_copy = ft_malloc(sizeof(char) * (ft_strlen(old_pwd) + 1), 0);
	ft_strlcpy(old_copy, old_pwd, ft_strlen(old_pwd) + 1);
	if (freeable)
		free(old_pwd);
	return (update_cwd(envpwd, old_copy, pathname));
}

int	cd_oldpwd(char **cmd, t_env *envpwd, char *tmp_cwd)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		if (envpwd->pwd)
			old_pwd = ft_strdup(envpwd->pwd);
		else
			return (1);
	}
	tmp_cwd = ft_malloc(sizeof(char) * (ft_strlen(old_pwd) + 1), 0);
	ft_strlcpy(tmp_cwd, old_pwd, ft_strlen(old_pwd) + 1);
	if (chdir(envpwd->oldpwd) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	return (update_cwd(envpwd, tmp_cwd, ft_strdup(envpwd->oldpwd)));
}

int	perror_and_return(char **cmd)
{
	perror(cmd[1]);
	return (1);
}
