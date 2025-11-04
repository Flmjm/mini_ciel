/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:42 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/03 18:07:24 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/pipex_bonus.h"

// char	*get_env_value(char *value, char **env)
// {
// 	size_t	len_value;
// 	size_t	i;

// 	len_value = ft_strlen(value);
// 	i = 0;
// 	while (env && env[i])
// 	{
// 		if (ft_strncmp(env[i], value, len_value) == 0)
// 			return (ft_strdup(env[i] + len_value));
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_pathname_dir(char *cmd)
{
	char	*temp;
	char	*path;
	char	buf[PATH_MAX];

	path = NULL;
	temp = ft_strjoin("/", cmd);
	path = ft_strjoin(getcwd(buf, PATH_MAX), temp);
	free(temp);
	return (path);
}

int	count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	cd_home(t_env *envpwd, char *pathname, char **env)
{
	char	buf[PATH_MAX];
	
	pathname = get_env_value("HOME=", env);
	if (!pathname)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return (1);
		}
		else
			return (update_cwd(envpwd, getcwd(buf, PATH_MAX), pathname));
}

int cd_oldpwd(char **cmd, t_env *envpwd, char *tmp_cwd)
{
	char	buf[PATH_MAX];
	tmp_cwd = getcwd(buf, PATH_MAX);
	if (chdir(envpwd->oldpwd) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	else
		return (update_cwd(envpwd, tmp_cwd, ft_strdup(envpwd->oldpwd)));
}

int	ft_cd(char **cmd, char **env, t_env *envpwd)
{
	char *pathname;
	char *tmp_cwd;
	char buf[PATH_MAX];

	//////////////////////////////////////////////
	pathname = NULL;
	tmp_cwd = NULL;
	printf("\\DEBUT\\\n oldpwd: %s\npwd: %s\n", envpwd->oldpwd, envpwd->pwd);
	if (count_args(cmd) != 0)
		return (1);
	/////// plutôt à gérer dans le parsing ? //////
	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0'))
		return(cd_home(envpwd, pathname, env));
	if (cmd[0] && cmd[1][0] == '-' && cmd[1][1] == '\0')
		return(cd_oldpwd(cmd, envpwd, tmp_cwd));
	pathname = get_pathname_dir(cmd[1]);
	tmp_cwd = getcwd(buf, PATH_MAX);
	if (chdir(pathname) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	else
		return (update_cwd(envpwd, tmp_cwd, pathname));
}

int	update_cwd(t_env *envpwd, char *s1_oldpwd, char *s2_pwd)
{
	envpwd->oldpwd = s1_oldpwd;
	envpwd->pwd = s2_pwd;
	printf("\\APRES FCT\\\n oldpwd: %s\npwd: %s\n", envpwd->oldpwd,
		envpwd->pwd);
	return (chdir(s2_pwd));
}

int cd_main(int ac, char **av, t_env *envpwd)
{
	// t_env	*envpwd;
	char		buf[PATH_MAX];

	// envpwd = ft_malloc(sizeof(t_env), 0);
	// envpwd->pwd = "OLDPWD=""/home/";
	envpwd->pwd = getcwd(buf, PATH_MAX);
	if (ac > 1)
	{
		ft_cd(av, envpwd->local_env, envpwd);
	}
}
