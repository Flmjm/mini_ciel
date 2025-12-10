/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:59:16 by mleschev          #+#    #+#             */
/*   Updated: 2025/12/10 14:54:10 by jmalaval         ###   ########.fr       */
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
	char	*line;

	signal_here_doc();
	close(pipefd[0]);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			close(pipefd[1]);
			exit(130);
		}
		if (ft_strncmp(line, delimiter, strlen(delimiter)) == 0
			&& strlen(line) == strlen(delimiter))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

void	signal_here_doc(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	printf_here_doc_error(char *delimiter)
{
	ft_printf("minishell: warning: here-document delimited by");
	ft_printf("end-of-file (wanted `");
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}
