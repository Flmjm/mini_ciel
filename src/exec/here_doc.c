/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:59:16 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/05 19:17:07 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

void	handler_heredoc(int sig)
{
	write(1, "\n", 1);
	exit(131);
}

void	here_doc_child(int *pipefd, char *delimiter)
{
	char				*line;
	struct sigaction	sa;

	sa.sa_handler = handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (1)
	{
		line = readline(">");
		if (!line)
			exit(130);
		if (ft_strncmp(line, delimiter, strlen(delimiter)) == 0
			&& strlen(line) == strlen(delimiter))
		{
			free(line);
			exit(0);
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}
