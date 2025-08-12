/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:42:21 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/16 23:04:51 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	printf_putstr(char *str);
int	printf_putnbr_base(long long nbr, const char *base);
int	printf_putnbr_p(void *p, const char *base);
int	printf_putnbr_x(int x, const char *base);

#endif
