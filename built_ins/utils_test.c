#include "../../include/exec.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

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
