/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:26:18 by yojin             #+#    #+#             */
/*   Updated: 2024/01/07 15:47:42 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_hex_digit(unsigned long long n)
{
	int	digit;

	digit = 1;
	while (n >= 16)
	{
		n /= 16;
		digit++;
	}
	return (digit);
}

int	ft_putptr(unsigned long long ptr)
{
	char	str[16];
	int		digit;
	int		idx;

	digit = get_hex_digit(ptr);
	idx = digit;
	if (write(1, "0x", 2) == -1)
		return (-1);
	while (--idx >= 0)
	{
		str[idx] = hex_to_char(ptr % 16, 0);
		ptr /= 16;
	}
	if (write(1, str, digit) == -1)
		return (-1);
	return (digit + 2);
}
