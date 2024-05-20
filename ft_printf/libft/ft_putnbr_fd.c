/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:45:02 by yojin             #+#    #+#             */
/*   Updated: 2024/01/07 15:54:07 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digit(long long n)
{
	int	digit;

	digit = 1;
	if (n < 0)
	{
		digit++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

int	ft_putnbr_fd(int n, int fd)
{
	char		str[10];
	long long	num;
	int			digit;
	int			idx;

	if (n == 0)
		return (write(fd, "0", 1));
	num = n;
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		num *= -1;
	}
	digit = get_digit(num);
	idx = digit;
	while (--idx >= 0)
	{
		str[idx] = num % 10 + '0';
		num /= 10;
	}
	if (write(fd, str, digit) == -1)
		return (-1);
	return (digit + (n < 0));
}
