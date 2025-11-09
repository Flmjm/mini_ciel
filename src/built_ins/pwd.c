/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:15:52 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/08 22:17:00 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

int ft_pwd()
{
    char buf[PATH_MAX];
    
    if (!getcwd(buf, PATH_MAX))
        return(1);
    else
        ft_putendl_fd(buf, 1);
    return(0);
}

