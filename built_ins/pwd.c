/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:15:52 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/10/20 23:52:56 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/pipex_bonus.h"
//check ok

int ft_pwd()
{
    char buf[PATH_MAX];

    if (!getcwd(buf, PATH_MAX))
        return(1);
    else
        ft_putendl_fd(buf, 1);
    return(0);
}

