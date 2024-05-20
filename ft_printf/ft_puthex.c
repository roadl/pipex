/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:18:16 by yojin             #+#    #+#             */
/*   Updated: 2024/01/07 16:21:11 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_hex_digit(unsigned int n)
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

int	ft_puthex(unsigned int hex, int is_upper)
{
	char	str[8];
	int		digit;
	int		idx;

	digit = get_hex_digit(hex);
	idx = digit;
	while (--idx >= 0)
	{
		str[idx] = hex_to_char(hex % 16, is_upper);
		hex /= 16;
	}
	if (write(1, str, digit) == -1)
		return (-1);
	return (digit);
}
