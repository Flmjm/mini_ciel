/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:46:35 by mleschev          #+#    #+#             */
/*   Updated: 2025/05/12 22:50:00 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			e_read;
	char		*line;
	static char	*bank;
	char		*buffer;

	e_read = 1;
	buffer = malloc(((BUFFER_SIZE + 1) * sizeof(char)));
	if (!buffer)
		return (NULL);
	if (!bank)
	{
		bank = malloc(BUFFER_SIZE + 1);
		if (!bank)
			return (NULL);
		bank[0] = '\0';
	}
	bank = reading(bank, e_read, fd, buffer);
	free(buffer);
	line = extract(bank);
	bank = clean(bank);
	return (line);
}

char	*extract(char *str)
{
	int		i;
	char	*line;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*clean(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	new_str = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*reading(char *bank, int e_read, int fd, char *buffer)
{
	char	*temp;

	while (!ft_strchr(bank, '\n') && e_read > 0)
	{
		e_read = read(fd, buffer, BUFFER_SIZE);
		if (e_read < 0)
			break ;
		buffer[e_read] = '\0';
		temp = ft_strjoin(bank, buffer);
		free(bank);
		bank = temp;
	}
	return (bank);
}
