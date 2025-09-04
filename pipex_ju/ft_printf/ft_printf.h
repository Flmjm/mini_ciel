/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:50:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/16 14:07:23 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_print_address(void *ptr);
int		ft_print_char(char c);
int		ft_print_int(int i);
int		ft_print_str(char *str);
int		ft_print_un_int(unsigned int i);
int		ft_print_x(unsigned int n, int x);
int		ft_putnbr_base(unsigned long long n, char *base, unsigned int len);
int		ft_printf(const char *s, ...);

#endif