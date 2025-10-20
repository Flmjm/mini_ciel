/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:42 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/10/07 15:04:50 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

// a modifier pour le .h du projet

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/// fonctions pour test ////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}
void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && str1[i] && str2[i] && (str1[i] == str2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return (str1[i] - str2[i]);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(s) + 1;
	str = malloc(size * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	else
	{
		while (s[i])
		{
			str[i] = s[i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	size_t			len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (len_src < size - 1)
		while (i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
	dst[i] = '\0';
	return (ft_strlen(src));
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	j;
	size_t			len_dst;
	size_t			len_src;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dst)
		return (size + len_src);
	else
	{
		while (dst[i])
			i++;
		while (src[j] && (i + j < size - 1))
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (len_dst + len_src);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (len + 2));
	ft_strlcat(str, s2, (len + 2));
	return (str);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/// fonctions pour test ////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

char	*get_env_value(char *value, char **env)
{
	size_t	len_value;
	size_t	i;

	len_value = ft_strlen(value);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], value, len_value) == 0)
			return (ft_strdup(env[i] + len_value));
		i++;
	}
	return (NULL);
}

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

int	cd_home(t_tmp_env *envpwd, char *pathname, char **env)
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

int cd_oldpwd(char **cmd, t_tmp_env *envpwd, char *tmp_cwd)
{
	char	buf[PATH_MAX];
	tmp_cwd = getcwd(buf, PATH_MAX);
	if (chdir(envpwd->oldpwd) != 0)
	{
		perror(cmd[1]);
		return (1);
	}
	else
		return (update_cwd(envpwd, tmp_cwd, envpwd->oldpwd));
}

int	ft_cd(char **cmd, char **env, t_tmp_env *envpwd) // a modifier pour ta struct env
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

int	update_cwd(t_tmp_env *envpwd, char *s1_oldpwd, char *s2_pwd)
{
	envpwd->oldpwd = s1_oldpwd;
	envpwd->pwd = s2_pwd;
	printf("\\APRES FCT\\\n oldpwd: %s\npwd: %s\n", envpwd->oldpwd,
		envpwd->pwd);
	return (chdir(s2_pwd));
}

int	main(int ac, char **av, char **env)
{
	t_tmp_env	*envpwd;
	char		buf[PATH_MAX];

	envpwd = malloc(sizeof(t_tmp_env));
	envpwd->oldpwd = "/home/jmalaval/Cercle_3/mini_ciel/src/";
	envpwd->pwd = getcwd(buf, PATH_MAX);
	if (ac > 1)
	{
		ft_cd(av + 1, env, envpwd);
	}
}

// tester avec la struct env de Manu
// locale 
