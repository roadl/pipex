/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:28:49 by yojin             #+#    #+#             */
/*   Updated: 2024/01/07 16:28:40 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

static size_t	get_digit(unsigned int n)
{
	int	digit;

	digit = 1;
	while (n >= 10)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

int	ft_putunbr(unsigned int i)
{
	char	str[10];
	int		digit;
	int		idx;

	digit = get_digit(i);
	idx = digit;
	while (--idx >= 0)
	{
		str[idx] = i % 10 + '0';
		i /= 10;
	}
	return (write(1, str, digit));
}
