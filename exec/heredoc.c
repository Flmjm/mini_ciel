/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:55:12 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/30 17:20:47 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../lib_parse.h"

// Utilisation exec
// if FILE_TYPE == HEREDOC, infile->fd = get_heredoc(infile->word_eof);

int get_heredoc(char *delimiter)
{
    int pipefd[2];
    char *line;
    
    if (pipe(pipefd) == -1)
        return(-1);
    while (1)
    {
        line = readline(">");
        if (!line || strncmp(line, delimiter, strlen(line)) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    return(pipefd[0]);
}
