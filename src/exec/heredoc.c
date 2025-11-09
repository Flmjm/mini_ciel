/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:55:12 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/08 15:24:04 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"
#include "../../include/lib_parse.h"

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
