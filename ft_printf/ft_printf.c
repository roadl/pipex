/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:06:04 by yojin             #+#    #+#             */
/*   Updated: 2024/01/07 16:24:04 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(const char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	if (c == 's')
		return (ft_putstr(va_arg(ap, void *)));
	if (c == 'p')
		return (ft_putptr(va_arg(ap, unsigned long long)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(ap, unsigned int), 1));
	if (c == 'u')
		return (ft_putunbr(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_puthex(va_arg(ap, unsigned int), 0));
	if (c == 'X')
		return (ft_puthex(va_arg(ap, unsigned int), 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (-1);
}

char	hex_to_char(int hex, int is_upper)
{
	char	c;

	if (hex < 10)
		return ('0' + hex);
	c = hex - 10 + 'a' - is_upper * 32;
	return (c);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count;
	int		temp;
	int		i;

	va_start(ap, s);
	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			temp = ft_print_format(s[++i], ap);
			if (temp == -1)
				return (-1);
			count += temp;
			continue ;
		}
		if (write(1, s + i, 1) == -1)
			return (-1);
		count++;
	}
	va_end(ap);
	return (count);
}
