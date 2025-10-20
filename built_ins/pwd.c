/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:15:52 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/10/07 15:04:14 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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

