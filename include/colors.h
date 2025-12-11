/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:16:16 by root              #+#    #+#             */
/*   Updated: 2025/12/11 12:05:06 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Reset
# define RESET       "\001\033[0m\002"

// Regular Colors
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define PURPLE      "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Bold Colors
# define BBLACK      "\033[1;30m"
# define BRED        "\033[1;31m"
# define BGREEN      "\033[1;32m"
# define BYELLOW     "\033[1;33m"
# define BBLUE       "\033[1;34m"
# define BPURPLE     "\033[1;35m"
# define BCYAN       "\001\033[1;36m\002"
# define BWHITE      "\001\033[1;37m\002"

// Underline Colors
# define UBLACK      "\033[4;30m"
# define URED        "\033[4;31m"
# define UGREEN      "\033[4;32m"
# define UYELLOW     "\033[4;33m"
# define UBLUE       "\033[4;34m"
# define UPURPLE     "\033[4;35m"
# define UCYAN       "\033[4;36m"
# define UWHITE      "\033[4;37m"

// Background Colors
# define ONBLACK     "\033[40m"
# define ONRED       "\033[41m"
# define ONGREEN     "\033[42m"
# define ONYELLOW    "\033[43m"
# define ONBLUE      "\033[44m"
# define ONPURPLE    "\033[45m"
# define ONCYAN      "\033[46m"
# define ONWHITE     "\033[47m"

#endif
