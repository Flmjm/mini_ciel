/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:58:39 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/17 03:49:26 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

char	*get_pathname_dir(char *cmd)
{
	char	*temp;
	char	*path;
	char	*cwd;

	path = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	temp = ft_strjoin("/", cmd);
	path = ft_strjoin(cwd, temp);
	free(cwd);
	return (path);
}

int	cd_home(t_env *envpwd, char *pathname, char **env)
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
		return (1);
	old_copy = ft_malloc(sizeof(char) * (ft_strlen(old_pwd) + 1), 0);
	ft_strlcpy(old_copy, old_pwd, ft_strlen(old_pwd) + 1);
	return (update_cwd(envpwd, old_copy, pathname));
}

int	cd_oldpwd(char **cmd, t_env *envpwd, char *tmp_cwd)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	tmp_cwd = ft_malloc(sizeof(char) * (ft_strlen(old_pwd) + 1), 0);
	ft_strlcpy(tmp_cwd, old_pwd, ft_strlen(old_pwd) + 1);
	free(old_pwd);
	if (chdir(envpwd->oldpwd) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	return (update_cwd(envpwd, tmp_cwd, ft_strdup(envpwd->oldpwd)));
}
